require 'helper'

module GDA
  class TestParser < TestCase
    attr_reader :parser

    def setup
      super
      @parser = GDA::SQL::Parser.new
    end

    def test_split
      assert_equal ['test', '"table"'], GDA.sql_identifier_split("test.\"table\"")
    end

    def test_parses
      assert parser.parse('SELECT * FROM FOO')
    end

    def test_providers
      assert_kind_of Array, GDA::SQL.providers
      assert_operator GDA::SQL.providers.length, :>, 0
    end

    def test_get_provider
      assert GDA::SQL::Provider.find SQL.providers.first
    end

    def test_provider_name
      name = SQL.providers.first
      provider = SQL::Provider.find name
      assert_equal name, provider.name
    end

    def test_pg_parser
      provider = SQL::Provider.find "PostgreSQL"
      skip "don't have PG provider" unless provider
      assert provider.parser.parse 'INSERT INTO "accounts" ("credit_limit", "firm_id", "firm_name") VALUES ($1, $2, $3) RETURNING "id"'
    end

    def test_mysql_parser
      provider = SQL::Provider.find "MySQL"
      skip "don't have MySQL provider" unless provider
      assert provider.parser.parse 'SELECT topics.* FROM topics WHERE topics.id = 147 LIMIT 1'

    end

    def test_id_quote
      provider = SQL::Provider.find "MySQL"
      skip "don't have MySQL provider" unless provider
      assert_equal '"1foo"', provider.quote("1foo")
    end

    def test_error
      assert_nil SQL::Provider.find "asdfasdfadsf"
    end
  end
end
