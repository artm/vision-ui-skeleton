require 'rspec'
require './ruby/guard/groupwrap'

describe GroupWrap do
  gw = GroupWrap.new { |s, tag|
    case tag
    when :paren
      "(#{s})"
    when :bracket
      "[#{s}]"
    end
  }

  it "should wrap groups" do
    gw.handle( /^E (\d+) (\w+)/, :paren, :bracket )
    gw.handle( /^W (\d+) (\w+)/, :bracket, :paren )
    gw.process("E 12 foo 1").should == "E (12) [foo] 1"
    gw.process("W 12 foo 2").should == "W [12] (foo) 2"
  end

  it "should deal with nested groups properly" do
    gw.handle( /^N (\w+?(\d+)\w+)/, :bracket, :paren )
    gw.handle( /^NN (\w+?(\d+(\w+?)\d+)\w+)/, :bracket, :paren, :bracket )
    gw.process("N foo12bar tail").should == "N [foo(12)bar] tail"
    gw.process("NN foo12quux13bar tail").should == "NN [foo(12[quux]13)bar] tail"
  end
end

