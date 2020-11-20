package Q51;

import java.util.*;
public class Solution {

    public List<List<String>> solveNQueens(int n) {
        char[][] chess = new char[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                chess[i][j] = '.';
        List<List<String>> res = new ArrayList<>();
        solve(res, chess, 0);
        return res;
    }

    /**
     *
     * @param res
     * @param chess
     * @param row
     */
    private void solve(List<List<String>> res, char[][] chess, int row) {
        if (row == chess.length) {
            // 递归终止，添加该种解法到 res
            res.add(construct(chess));
            return;
        }
        for (int col = 0; col < chess.length; col++) {
            // 遍历行号为row的 每个列col

            if (valid(chess, row, col)) {
                // 当前位置没有皇后 & 当前位置右上没有皇后 & 当前位置左上没有皇后

                // 设置当前位置为 Q
                chess[row][col] = 'Q';
                // 开始递归下一行
                solve(res, chess, row + 1);
                // 递归结束，重置当前位置为 .
                chess[row][col] = '.';
            }
        }
    }

    /**
     * 判断chess[row][col]是否可以放置皇后
     *
     * @param chess 棋盘
     * @param row   当前位置行号（从0开始）
     * @param col   当前位置列号（从0开始）
     * @return 是否可以放置皇后
     */
    private boolean valid(char[][] chess, int row, int col) {
        // 判断当前坐标的正上方有没有皇后
        for (int i = 0; i < row; i++) {
            if (chess[i][col] == 'Q') {
                return false;
            }
        }
        // 判断当前坐标的右上角有没有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < chess[i].length; i--, j++) {
            if (chess[i][j] == 'Q') {
                return false;
            }
        }
        // 判断当前坐标的左上角有没有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chess[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }

    /**
     * 将 二维数组 chess 转为 List 以便输出题解
     * @param chess
     * @return
     */
    private List<String> construct(char[][] chess) {
        List<String> path = new ArrayList<>();
        for (int i = 0; i < chess.length; i++) {
            path.add(new String(chess[i]));
        }
        return path;
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        List<List<String>> l = s.solveNQueens(4);
        System.out.println(l);
    }

}
