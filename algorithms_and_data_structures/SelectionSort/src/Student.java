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
//        if(this.scope < another.scope){
//            return -1;
//        }else if(this.scope == another.scope){
//            return 0;
//        }else {
//            return 1;
//        }
        return this.scope - another.scope;
    }

    @Override
    public String toString() {
        return String.format("Student(name:%s, scope:%d)", this.name, this.scope);
    }
}
