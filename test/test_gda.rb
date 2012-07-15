require 'helper'

module GDA
  class TestParser < TestCase
    attr_reader :parser

    def setup
      @parser = GDA::SQL::Parser.new
    end

    def test_parses
      assert parser.parse('SELECT * FROM FOO')
    end
  end
end
