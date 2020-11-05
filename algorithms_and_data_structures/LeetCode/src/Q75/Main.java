package Q75;

public class Main {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] colors = {2, 0, 2, 1, 1, 0};
        s.sortColors(colors);

        for (int color : colors) {
            System.out.println(color);
        }

    }
}
