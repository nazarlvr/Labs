merge :: [Int] -> Int -> Int -> [Int]
merge x n t= [ x !! y | y <- [0..((length x) - 1)], (mod y t) == n]

main = do
    let g = [1..10]
    let q = 2
    print ([merge g k q | k <- [0..(q-1)]])
    let g = [1,5,3,4,1,2,3]
    let q = 5
    print ([merge g k q | k <- [0..(q-1)]])
    let g = [1,1,1,2,3]
    let q = 10
    print ([merge g k q | k <- [0..(q-1)]])