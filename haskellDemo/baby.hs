doubleMe x = x + x
-- doubleUs x y = x * 2 + y * 2
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNumber x = if x > 100 then x else x * 2
conanO'Brien = "It's a-me, Conan O'Brien!"
lostNumbers = [4,8,15,16,23,48] 

-- 遍历 List xs，奇数且小于10替换为"BOOM!"" 奇数切大于10替换为 "BANG!"
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

-- 仿写 length
length' xs = sum [1 | _ <- xs]

-- 去除所有小写字母
removeNoneUppercase st = [c | c <- st, c `elem` ['A'..'Z']]

triangles zc = [(a,b,c) | c <- [1..zc], b <- [1..zc], a <- [1..zc], a + b > c, a - b < c , a+c>b, a-c<b, ]

rightTriangles tr zc= [ (a,b,c) | (a,b,c) <- tr, a^2 + b^2 == c^2, a + b + c == zc]