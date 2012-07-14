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
        assert stmt.ast
        assert stmt.ast.from
      end

      def test_distinct_expr
        assert_nil stmt.ast.distinct_expr
      end

      def test_expr_list
        assert_equal 1, stmt.ast.expr_list.length

        stmt.ast.expr_list.each do |node|
          assert node
        end
      end

      def test_where_cond
        assert stmt.ast.where_cond
      end

      def test_group_by
        assert stmt.ast.group_by
        stmt.ast.group_by.each do |node|
          assert node
        end
      end

      def test_having_cond
        assert stmt.ast.having_cond
      end

      def test_order_by
        assert_equal 2, stmt.ast.order_by.length
        stmt.ast.order_by.each do |node|
          assert node
        end
      end

      def test_limit_count
        assert stmt.ast.limit_count
      end

      def test_limit_offset
        assert stmt.ast.limit_offset
      end

      def test_distinct?
        refute stmt.ast.distinct?
      end

      def test_each
        yielded = false
        stmt.ast.each do |node|
          yielded = true
          assert node
        end
        assert yielded
      end
    end
  end
end
