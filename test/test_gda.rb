require 'minitest/autorun'
require 'gda'

class TestGda < MiniTest::Unit::TestCase
  attr_reader :parser

  def setup
    @parser = GDA::SQL::Parser.new
  end

  def test_parses
    assert parser.parse('SELECT * FROM FOO')
  end
end
