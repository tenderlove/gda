# -*- encoding: utf-8 -*-
# stub: gda 1.1.0.20190320134558 ruby lib
# stub: ext/gda/extconf.rb

Gem::Specification.new do |s|
  s.name = "gda".freeze
  s.version = "1.1.0.20190320134558"

  s.required_rubygems_version = Gem::Requirement.new(">= 0".freeze) if s.respond_to? :required_rubygems_version=
  s.require_paths = ["lib".freeze]
  s.authors = ["Aaron Patterson".freeze]
  s.date = "2019-03-20"
  s.description = "An SQL parser. Wraps libgda in a loving embrace to give you a ruby level SQL\nparser.".freeze
  s.email = ["tenderlove@ruby-lang.org".freeze]
  s.extensions = ["ext/gda/extconf.rb".freeze]
  s.extra_rdoc_files = ["CHANGELOG.rdoc".freeze, "Manifest.txt".freeze, "README.rdoc".freeze, "CHANGELOG.rdoc".freeze, "README.rdoc".freeze]
  s.files = [".autotest".freeze, "CHANGELOG.rdoc".freeze, "Manifest.txt".freeze, "README.rdoc".freeze, "Rakefile".freeze, "ext/gda/extconf.rb".freeze, "ext/gda/gda.c".freeze, "ext/gda/gda.h".freeze, "ext/gda/gda_nodes.c".freeze, "ext/gda/gda_nodes.h".freeze, "ext/gda/gda_provider.c".freeze, "ext/gda/gda_provider.h".freeze, "ext/gda/gda_statement.c".freeze, "ext/gda/gda_statement.h".freeze, "lib/gda.rb".freeze, "lib/gda/visitors/dot.rb".freeze, "lib/gda/visitors/each.rb".freeze, "lib/gda/visitors/max_depth.rb".freeze, "lib/gda/visitors/visitor.rb".freeze, "test/helper.rb".freeze, "test/sqllog.sqlite3".freeze, "test/test_dot_visitor.rb".freeze, "test/test_gda.rb".freeze, "test/test_max_depth.rb".freeze, "test/test_node_attributes.rb".freeze, "test/test_nodes.rb".freeze, "test/test_statement.rb".freeze]
  s.homepage = "http://github.com/tenderlove/gda".freeze
  s.licenses = ["MIT".freeze]
  s.rdoc_options = ["--main".freeze, "README.rdoc".freeze]
  s.required_ruby_version = Gem::Requirement.new(">= 1.9.3".freeze)
  s.rubygems_version = "3.0.1".freeze
  s.summary = "An SQL parser".freeze

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<minitest>.freeze, ["~> 5.11"])
      s.add_development_dependency(%q<rake-compiler>.freeze, [">= 0.4.1"])
      s.add_development_dependency(%q<sqlite3>.freeze, [">= 0"])
      s.add_development_dependency(%q<rdoc>.freeze, [">= 4.0", "< 7"])
      s.add_development_dependency(%q<hoe>.freeze, ["~> 3.17"])
    else
      s.add_dependency(%q<minitest>.freeze, ["~> 5.11"])
      s.add_dependency(%q<rake-compiler>.freeze, [">= 0.4.1"])
      s.add_dependency(%q<sqlite3>.freeze, [">= 0"])
      s.add_dependency(%q<rdoc>.freeze, [">= 4.0", "< 7"])
      s.add_dependency(%q<hoe>.freeze, ["~> 3.17"])
    end
  else
    s.add_dependency(%q<minitest>.freeze, ["~> 5.11"])
    s.add_dependency(%q<rake-compiler>.freeze, [">= 0.4.1"])
    s.add_dependency(%q<sqlite3>.freeze, [">= 0"])
    s.add_dependency(%q<rdoc>.freeze, [">= 4.0", "< 7"])
    s.add_dependency(%q<hoe>.freeze, ["~> 3.17"])
  end
end
