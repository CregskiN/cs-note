public class LinearSearch {

    private LinearSearch() {
    }

    /**
     * 查询data中的target，并返回下标
     *
     * @param data
     * @param target
     * @return index
     */
    public static <E> int search(E data[], E target) {
        for (int i = 0; i < data.length; i++) {
            // 这里是两个类对象
            if (data[i].equals(target)) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
//        Integer[] data = {1,2,3,4,5,6,7,8};
//        int res = LinearSearch.search(data, 7); // target 自动转换基本数据类型，数组data不能自动转换
//        System.out.println(res);
//
//        int res2 = LinearSearch.search(data, 22);
//        System.out.println(res2);
//
//        Student[] students = {new Student("Alice"), new Student("Bobo"), new Student("Charles")};
//        Student bobo = new Student("bobo");
//        int res3 = LinearSearch.search(students, bobo);
//        System.out.println(res3);
        int[] dataSize = {1000000, 10000000};
        for (int n : dataSize) {
            Integer[] data = ArrayGenerator.generateOrderArray(n);
            long startTime = System.nanoTime();
            for (int i = 0; i < 100; i++) {
                // 重复100次函数，取耗时平均值
                LinearSearch.search(data, n);
            }
            long endTime = System.nanoTime();
            System.out.println("n = " + n + ", runs 100, time = " + (endTime - startTime) / 1000000000.0 / 100);
        }

    }
}
