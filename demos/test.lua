function birdie_index(self, i)
  if i == "name" then return "MrFigs"
  elseif i == "num_wings" then return 2
  end
end
function birdie_setindex(self, i, x) return nil end

Birdie = {}
setmetatable(Birdie, Birdie)
function Birdie:__index(i) return birdie_index(self, i) end
function Birdie:__setindex(i, x) return birdie_setindex(self, i, x) end
function Birdie.__call()
  local self = {}
  setmetatable(self, Birdie)
  return self
end

bird = Birdie()
print(bird.name)
print(bird.num_wings)