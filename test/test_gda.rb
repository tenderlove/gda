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
  end
end
