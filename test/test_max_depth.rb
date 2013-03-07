require 'helper'

module GDA
  module Visitors
    class TestMaxDepth < TestCase
      attr_reader :parser

      def setup
        super
        @parser = GDA::SQL::Parser.new
      end

      def test_depth
        stmt = parser.parse('SELECT * FROM FOO')
        assert_equal 5, stmt.ast.max_depth
      end
    end
  end
end
