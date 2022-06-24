excludedublicates :: [Int] -> [Int]
excludedublicates x = [ x !! z | z <- [0..((length x) - 1)], length [ y | y <- [0..(z - 1)], x !! z == x !! y] == 0]

main = do
    let g = [1,2,3,2,3,1,5,2,3,4,5,2]
    print (excludedublicates g) 
    let r = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
    print (excludedublicates r) 
    let q = [1..100]
    print (excludedublicates q) 
     
     