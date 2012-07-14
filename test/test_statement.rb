require 'minitest/autorun'
require 'gda'

module GDA
  module SQL
    class TestStatement < MiniTest::Unit::TestCase
      attr_reader :parser, :stmt

      def setup
        @parser = GDA::SQL::Parser.new
        @stmt = parser.parse 'SELECT * FROM FOO WHERE 1 = 1 GROUP BY omg'
      end

      def test_serialize
        assert stmt.serialize
      end

      def test_node
        assert stmt.node
        assert stmt.node.from
        assert_nil stmt.node.distinct_expr

        assert_equal 1, stmt.node.expr_list.length

        stmt.node.expr_list.each do |node|
          assert node
        end

        assert stmt.node.where_cond
        assert stmt.node.group_by
        stmt.node.group_by.each do |node|
          assert node
        end
      end
    end
  end
end
