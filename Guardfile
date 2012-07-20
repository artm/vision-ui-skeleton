require './ruby/guard/helpers'

notification :growl
ignore_paths 'build', 'release', 'vendor'

guard :bundler do
  watch('Gemfile')
end

guard :rspec, :version => 2, :spec_paths => ["ruby/spec"] do
  watch(%r{^ruby/spec/.+_spec\.rb$})
  watch(%r{^ruby/.*/([^/]+)\.rb$}) { |m| "ruby/spec/#{m[1]}_spec.rb" }
end

# Poor mans CT/CI
guard :shell do
  watch(/CMakeLists.txt$|\.cmake$|\.(cpp|h|hpp)$/) do |m|
    # ignore_paths doesn't seem to work
    unless m[0] =~ %r{^(build|release|vendor|lib/cxxtest)/}
      message("Rebuilding because #{m[0]} has changed", :title => 'Make')
      puts
      File.open("build.log", "w") do |log|
        execute 'time make -C build', :title => "Make", :log => log
      end
    end
  end

  cxxtest_color = GroupWrap.new { |text, hilite| color(text,hilite) }
  cxxtest_color.handle %r{^In (.+)$}, :blue
  cxxtest_color.handle %r{^([^:]+):(\d+): (Error: .*)$}, :blue, :blue, :red

  watch(%r{build/test/test_[^/]+}) do |m|
    file = m[0]
    if File.executable?(file)
      name = File.basename(file)
      File.open("test.log", "w") do |log|
        execute("#{file}", :title => "Test #{name}", :log => log) do |s|
          puts cxxtest_color.process(s)
        end
      end
    end
  end
end

