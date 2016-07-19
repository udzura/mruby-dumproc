##
## Dumproc Test
##

assert("Dumproc#hello") do
  t = Dumproc.new "hello"
  assert_equal("hello", t.hello)
end

assert("Dumproc#bye") do
  t = Dumproc.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Dumproc.hi") do
  assert_equal("hi!!", Dumproc.hi)
end
