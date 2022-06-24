fibonacci :: Int -> Int -> Int -> Bool
fibonacci x y z | y > x = False 
	| y == x = True
	| otherwise = fibonacci x z (y + z)
main = do
    let g = [1..100]
    print ([[x | x <- g, fibonacci x 1 1], [x | x <- g, not (fibonacci x 1 1)]])		
    let r = [1,1,1,1,1,5,5,5,5,4,4,4,4,4,4,4,4]
    print ([[x | x <- r, fibonacci x 1 1], [x | x <- r, not (fibonacci x 1 1)]])
    let q = [4,6,7,9,10,11,12]
    print ([[x | x <- q, fibonacci x 1 1], [x | x <- q, not (fibonacci x 1 1)]])
     