require 'minitest/autorun'
require 'gda'

module GDA
  module SQL
    class TestStatement < MiniTest::Unit::TestCase
      attr_reader :parser, :stmt

      def setup
        @parser = GDA::SQL::Parser.new
        @stmt = parser.parse 'SELECT * FROM FOO WHERE 1 = 1 GROUP BY omg HAVING omg(id) < 2 ORDER BY foo, bar LIMIT 50 OFFSET 2'
      end

      def test_serialize
        assert stmt.serialize
      end

      def test_from
        assert stmt.node
        assert stmt.node.from
      end

      def test_distinct_expr
        assert_nil stmt.node.distinct_expr
      end

      def test_expr_list
        assert_equal 1, stmt.node.expr_list.length

        stmt.node.expr_list.each do |node|
          assert node
        end
      end

      def test_where_cond
        assert stmt.node.where_cond
      end

      def test_group_by
        assert stmt.node.group_by
        stmt.node.group_by.each do |node|
          assert node
        end
      end

      def test_having_cond
        assert stmt.node.having_cond
      end

      def test_order_by
        assert_equal 2, stmt.node.order_by.length
        stmt.node.order_by.each do |node|
          assert node
        end
      end

      def test_limit_count
        assert stmt.node.limit_count
      end

      def test_limit_count
        assert stmt.node.limit_offset
      end

      def test_distinct?
        refute stmt.node.distinct?
      end
    end
  end
end
