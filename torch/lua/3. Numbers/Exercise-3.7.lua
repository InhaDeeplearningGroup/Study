#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-3.7.lua

-- Write a function to produce a psedu-random number 
-- with a standard normal (Gaussian) distribution

--[[
for i = 1, 3 do
  print(math.random())  -- Always sme value..
end


math.randomseed(os.time())
for i = 1, 3 do
  print(math.random(1, 10))  -- Always different value!!
end
]]--


-- Therefore.
function n_gaussian_distribution(x, mu, sigma)
  return math.exp(-.5 * (x-mu)*(x-mu)/(math.random(1, sigma)) * (math.random(1, sigma))) / math.sqrt(2.0*math.pi*(math.random(1, sigma))*(math.random(1, sigma)))
end


  x = 5
  mu = 10
  sigma = .3

  print(n_gaussian_distribution(x, mu, sigma))
  