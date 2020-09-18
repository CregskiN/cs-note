doubleMe x = x + x
-- doubleUs x y = x * 2 + y * 2
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNumber x = if x > 100 then x else x * 2
conanO'Brien = "It's a-me, Conan O'Brien!"
lostNumbers = [4,8,15,16,23,48] 

-- 遍历 List xs，奇数且小于10替换为"BOOM!"" 奇数切大于10替换为 "BANG!"
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

-- 仿写 length -- List Comprehension
-- length' xs = sum [1 | _ <- xs]

-- 去除所有小写字母
removeNoneUppercase :: String -> String
removeNoneUppercase st = [c | c <- st, c `elem` ['A'..'Z']]

triangles zc = [(a,b,c) | c <- [1..zc], b <- [1..zc], a <- [1..zc], a + b > c, a - b < c , a+c>b, a-c<b ]

rightTriangles tr zc= [ (a,b,c) | (a,b,c) <- tr, a^2 + b^2 == c^2, a + b + c == zc]

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z

-- 模式匹配
lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBERS SEVEN."
lucky x = "Sorry, you are out of lucky."

--
sayMe :: (Integral a) => a -> String
sayMe 1 = "Number 1"
sayMe 2 = "Number 2"
sayMe 3 = "Number 3"
sayMe 4 = "Number 4"
sayMe 5 = "Number 5"
sayMe x = "Number not between 1 and 5"



-- 递归
factorial :: (Integral a) => a -> a
factorial 0 = 1 -- 先捕获0，作为终止条件
factorial n = n * factorial(n-1)

addVectors :: (Num n) => (n, n) -> (n, n) -> (n, n)
addVectors (a, b) (c, d) = (a+c, b+d)

addVectors' :: (Num n) => (n, n) -> (n, n) -> (n, n)
addVectors' a b = (fst a + fst b, snd a + snd b)
-- 并不好用，无法解决三元组

first :: (a, b, c) -> a
first (a, _, _) = a

second :: (a, b, c) -> b
second (_, b, _) = b

head' :: [a] -> a
head' [] = error "you can't get first item from empty list."
head' (x:_) = x -- _起到 ...rest 作用

-- 
tell :: (Show l) => [l] -> String
tell [] = error "the list is empty."
tell (x:[]) = "The list has one element " ++ show x
tell (x:y:[]) = "The list has two elements " ++ show x ++ " and " ++ show y
tell (x:y:_) = "The list is long. The first two elements are " ++ show x ++ " and " ++ show y

-- 重写 length 递归实现
length' :: (Num b) => [a] -> b
length' [] = 0
length' (_:xs) = 1 + length' xs

-- 递归实现累加
sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs