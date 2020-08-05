public class Student {
    public String name;

    public Student(String name) {
        this.name = name;
    }

    /**
     * 大小写模糊
     * @param student
     * @return
     */
    @Override
    public boolean equals(Object student) {
        if(this == student){
            // 如果双方是同一个实例对象
            return true;
        }
        if(student == null){
            // 如果接收的实例对象为空
            return false;
        }
        if(this.getClass() != student.getClass()){
            // 如果这两个实例，不属于同一个类
            return false;
        }
        Student another = (Student) student;
        return this.name.toLowerCase().equals(another.name.toLowerCase());
    }
}
