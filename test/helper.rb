require 'minitest/autorun'
require 'gda'
require 'sqlite3'

module GDA
  class TestCase < MiniTest::Unit::TestCase
    @rails_sql = nil

    def self.rails_sql
      return @rails_sql if @rails_sql

      db_file = File.join File.dirname(__FILE__), 'sqllog.sqlite3'
      db      = SQLite3::Database.new db_file
      @rails_sql = db.execute('SELECT * FROM sqllog').map(&:first)
    end
  end
end
