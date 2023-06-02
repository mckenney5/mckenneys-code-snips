# Ruby
# Takes user input and says hello
# to run: ruby ruby.rs 

#!/usr/bin/ruby

# prompt
print "Enter your name: "

# get input
name = gets

# remove new line char
name.delete!("\n")

# say hello
print "Hello #{name}!\n"

