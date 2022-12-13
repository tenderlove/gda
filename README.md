# gda

* http://github.com/tenderlove/gda

## DESCRIPTION

An SQL parser. Wraps libgda in a loving embrace to give you a ruby level SQL
parser.

# SYNOPSIS

```ruby
parser = GDA::SQL::Parser.new

stmt = parser.parse 'SELECT * FROM FOO WHERE 1 = 1 GROUP BY omg HAVING omg(id) < 2 ORDER BY foo, bar LIMIT 50 OFFSET 2'

stmt.ast.each do |node|
  p node
end

puts stmt.ast.to_dot
```

## HACKING

    $ brew install libgda
    $ gem install hoe rake-compiler
    $ rake

## INSTALL


    $ brew install libgda
    $ gem install gda

## LICENSE

(The MIT License)

Copyright (c) 2012-2016 Aaron Patterson

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
