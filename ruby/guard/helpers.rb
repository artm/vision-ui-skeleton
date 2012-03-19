require 'guard'
require './ruby/guard/groupwrap'

def color(text, *color_options)
  if Symbol === color_options
    color_options = [color_options]
  end
  color_code = ''
  color_options.each do |color_option|
    color_option = color_option.to_s
    if color_option != ''
      if !(color_option =~ /\d+/)
        color_option = ::Guard::UI::const_get("ANSI_ESCAPE_#{ color_option.upcase }")
      end
      color_code += ';' + color_option
    end
  end
  "\e[0#{ color_code }m#{ text }\e[0m"
end

def message(mess, options = {})
  if options[:image] == :failed
    puts color(mess, :red)
  elsif options[:image] == :success
    puts color(mess, :green)
  else
    puts mess
  end
  ::Guard::Notifier::notify(mess, options)
end

def execute(command, options = {}, &block)
  exit_code = Open3.popen2e(command) { | stdin, stdout, wait_thr |
    block ||= Proc.new {|s| puts s }
    stdout.each do |s|
      if options[:log]
        options[:log].puts s
      end
      block.call(s)
    end
    wait_thr.value
  }

  if exit_code == 0
    message (options[:success] || "#{command} succeded"),
            :title => (options[:title] || "shell"),
            :image => :success
  else
    message (options[:failure] || "#{command} failed"),
            :title => (options[:title] || "shell"),
            :image => :failed
  end

  exit_code
end

