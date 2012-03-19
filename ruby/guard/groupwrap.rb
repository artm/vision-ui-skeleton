class GroupWrap
  def initialize(&block)
    @wrap = block
    @transformers = []
  end

  def handle(pattern, *tags)
    @transformers << [pattern, *tags]
  end

  def range_tree(m, tags)
    stack = []
    tree = []

    (1...m.length).each do |i|
      r = { :begin => m.begin(i), :end => m.end(i), :tag => tags[i], :children => [] }

      catch :inserted do
        while !stack.empty?
          if stack.last[:end] <= r[:begin] &&
            stack.pop
          else
            # nest
            stack.last[:children] << r
            stack.push r
            throw :inserted
          end
        end
        stack.push r
        tree << r
      end
    end

    tree
  end

  def recursive_wrap(str, range, from=0, to=str.length)
    if range == []
      "#{str[from...to]}"
    elsif Hash === range
      @wrap.call(
        recursive_wrap(str, range[:children], range[:begin], range[:end]),
        range[:tag])
    else
      # handling a list of trees
      cursor = from
      accu = ""
      range.each do |range|
        replacement = recursive_wrap(str, range)
        accu += str[cursor...range[:begin]] + replacement
        cursor = range[:end]
      end
      accu += str[cursor...to]
    end
  end

  def process(str)
    @transformers.each do |tags|
      pattern = tags[0]
      pattern.match(str) do |m|
        return recursive_wrap(str, range_tree(m, tags))
      end
    end
    str
  end
end
