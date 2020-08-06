public class Student implements Comparable<Student> {
    public String name;
    public int scope;

    public Student(String name, int scope) {
        this.name = name;
        this.scope = scope;
    }

    /**
     * 大小写模糊
     *
     * @param student
     * @return
     */
    @Override
    public boolean equals(Object student) {
        if (this == student) {
            // 如果双方是同一个实例对象
            return true;
        }
        if (student == null) {
            // 如果接收的实例对象为空
            return false;
        }
        if (this.getClass() != student.getClass()) {
            // 如果这两个实例，不属于同一个类
            return false;
        }
        Student another = (Student) student;
        return this.name.toLowerCase().equals(another.name.toLowerCase());
    }

    /**
     * > 1，= 0，< -1
     *
     * @param another
     * @return
     */
    @Override
    public int compareTo(Student another) {
        return this.scope - another.scope;
    }

    @Override
    public String toString() {
        return String.format("Student(name:%s, scope:%d)", this.name, this.scope);
    }


    public static void main(String[] args) {
        Array<Student> arr = new Array<Student>(3);
        arr.addLast(new Student("Alice", 100));
        arr.addLast(new Student("Bobo", 70));
        arr.addLast(new Student("Charles", 85));
        arr.addLast(new Student("Charles", 85));
        arr.removeLast();
        System.out.println(arr);
    }
}
