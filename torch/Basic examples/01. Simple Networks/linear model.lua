require 'torch'
require 'nn'
require 'math'
require 'optim'
require 'gnuplot'
require 'dataset'

torch.manualSeed(0)

-----------------------------------------------------------------
-- Set parset arguments
-----------------------------------------------------------------

local optimState
local optimMethod

local opt = {}
opt.optimization = 'sgd'
opt.batch_size = 1000
opt.train_size = 60000
opt.test_size = 0
opt.epochs = 10
  
if opt.optimization == 'sgd' then
  optimState = {
    learningRate = 1e-1,
    momentum = 0,
    weightDecay = 0,
    learningRateDecay = 1e-7
  }
  optimMethod = optim.sgd
  
elseif opt.optimization == 'adagrad' then
  optimState = {
    learningRate = 1e-1
  }
  optimMethod = optim.adagrad
else
  error('[INFO] Unknown optimizer')
end

-----------------------------------------------------------------
-- Download and load MNIST dataset
-----------------------------------------------------------------

mnist.download()

local function load_dataset(train_or_test, count)
    local data
    if train_or_test == 'train' then
        data = mnist.loadTrainset(count, {32, 32})
    else
        data = mnist.loadTestset(count, {32, 32})
    end

    local shuffled_ind = torch.randperm(data.data:size(1)):long()
    data.data = data.data:index(1, shuffled_ind):squeeze()
    data.labels = data.labels:index(1, shuffled_ind):squeeze()

    -- gnuplot.imagesc(data.data[10])    -- Visualize MNIST data

    data.data = data.data:reshape(data.data:size(1), 32*32)

    print(' loaded dataset "' .. train_or_test .. '"')
    print('inputs', data.data:size())
    print('targets', data.labels:size())

    return data
end

local train = load_dataset('train', opt.train_size)
local test = load_dataset('test', opt.test_size)

-----------------------------------------------------------------
-- Build model
-----------------------------------------------------------------

local n_train_data = train.data:size(1)
local n_inputs = train.data:size(2)
local n_outputs = train.labels:max()

print("[INFO] MNIST label is: " .. train.labels:max())
print("-----------------------------------------\n")

local lin_layer = nn.Linear(n_inputs, n_outputs)
local softmax = nn.LogSoftMax()
local model = nn.Sequential()

model:add(lin_layer)
model:add(softmax)

local n_test_data = test.data:size(1)

-----------------------------------------------------------------
-- Loss function
-----------------------------------------------------------------

local criterion = nn.ClassNLLCriterion()

-----------------------------------------------------------------
-- Model training
-----------------------------------------------------------------

local parameters, gradParameters = model:getParameters()

-----------------------------------------------------------------
-- Define closer with mini-batch
-----------------------------------------------------------------

local c = 0
local feval = function(x)
  if x ~= parameters then
    parameters:copy(x)
  end
  
  local start_ind = c * opt.batch_size + 1
  local end_ind = math.min(n_train_data, (c + 1) * opt.batch_size + 1)
  if end_ind == n_train_data then 
    c = 0
  else
    c = c + 1
  end
  
  local batch_inputs = train.data[{ {start_ind, end_ind}, {} }]
  local batch_labels = train.labels[{ {start_ind, end_ind} }]
  
  gradParameters:zero()    -- Set model's gradients zero.
  
  local batch_outputs = model:forward(batch_inputs)
  local batch_loss = criterion:forward(batch_outputs, batch_labels)
  local dloss_output = criterion:backward(batch_outputs, batch_labels)
  model:backward(batch_inputs, dloss_output)
  
  return batch_loss, gradParameters
end

local train_loss = {}
local epochs = opt.epochs
local iterations = epochs * math.ceil(n_train_data / opt.batch_size)
  
for i = 1, iterations do
  local _, minibatch_loss = optimMethod(feval, parameters, optimState)    -- Important line for training
  
  if i % 50 == 0 then
    print(string.format("[Train] current iteration: %6s, current loss: %6.6f", i, minibatch_loss[1]))    -- Process information
  end
  train_loss[#train_loss + 1] = minibatch_loss[1]    -- Add mini-batch loss to total loss
end
print("-----------------------------------------\n")
  
-----------------------------------------------------------------
-- Evaluate test error
-----------------------------------------------------------------

local test_loss = {}
local epochs = opt.epochs
local iterations = 1 * math.ceil(n_test_data / opt.batch_size)

for i = 1, iterations do
  local _, minibatch_loss = optimMethod(feval, parameters, optimState)
  if i % 5 == 0 then
    print(string.format("[Test] current iteration: %6s, current loss: %6.6f", i, minibatch_loss[1]))
  end
  test_loss[#test_loss + 1] = minibatch_loss[1]
end
print("-----------------------------------------\n")

-----------------------------------------------------------------
-- Test trained model
-----------------------------------------------------------------

local log_probabilities = model:forward(test.data)
local probabilities = torch.exp(log_probabilities)
local _, max_probabilities = torch.max(probabilities, 2)

n_correct_labels = 0
n_testData = #(test.data)

for i = 1, n_testData[1] do
  if max_probabilities[i][1] == test.labels[i] then
    n_correct_labels = n_correct_labels + 1
  end
end

-----------------------------------------------------------------
-- Calculate and total accuracy
-----------------------------------------------------------------

print("[INFO] number of correct labels: " .. tostring(n_correct_labels))
total_acc = n_correct_labels / n_testData[1] * 100
print("[INFO] Total accuracy: " .. tostring(total_acc) .. "%")
print("-----------------------------------------\n")



