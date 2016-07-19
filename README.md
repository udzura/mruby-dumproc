# mruby-dumproc   [![Build Status](https://travis-ci.org/udzura/mruby-dumproc.svg?branch=master)](https://travis-ci.org/udzura/mruby-dumproc)
Dumproc class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-dumproc'
end
```
## example
```ruby
p Dumproc.hi
#=> "hi!!"
t = Dumproc.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
