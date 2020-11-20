public class MinimumSpanningTree {
    int[][] map;

    public MinimumSpanningTree(int[][] map) {
        this.map = map;
    }

    /**
     * @param startNodeIndex 根节点下标
     * @return 普里姆算法生成树，数组表示
     */
    public int[] prim(int startNodeIndex) {
        int[][] map = this.copyMap(this.map);
        boolean[] selected = new boolean[map.length];
        int[] minDist = new int[map.length];
        int[] parent = new int[map.length];

        // 初始化
        for (int i = 0; i < selected.length; i++) {
            selected[i] = false;
            minDist[i] = Integer.MAX_VALUE;
            parent[i] = -1;
        }
        selected[startNodeIndex] = true;
        parent[startNodeIndex] = Integer.MAX_VALUE;


        /**
         * 1. Update 更新所有与当前选中的顶点集相连的 minDist、parent
         * 2. Scan 扫描得 update 更新的顶点中（未选中的顶点），minDist 最小的定点
         * 3. Add 将 Scan 中扫描到的点的 selected 更新
         */
        while (!this.isFinished(selected)) {
            this.update(map, selected, minDist, parent);
            int nodeIndex = this.scan(selected, minDist);
            this.add(selected, nodeIndex);

        }

        return parent;
    }

    private void update(int[][] map, boolean[] selected, int[] minDist, int[] parent) {
        for (int i = 0; i < selected.length; i++) {
            // 遍历所有顶点
            if (!selected[i]) {
                // 找出未选入的节点下标i
                int weight = Integer.MAX_VALUE;
                for (int j = 0; j < selected.length; j++) {
                    if (selected[j]) {
                        // 找出已选入的节点下标j
                        if (map[i][j] < weight) {
                            // 如果当前选中的i、j边权，小于之前选中的
                            weight = map[i][j]; // 得到i、j边权
                            minDist[i] = weight; // 赋值
                            parent[i] = j;
                        }
                    }
                }
            }
        }
    }

    private int scan(boolean[] selected, int[] minDist) {
        int minWeight = Integer.MAX_VALUE;
        int index = -1;
        for (int i = 0; i < minDist.length; i++) {
            if (!selected[i] && minDist[i] < minWeight) {
                index = i;
                minWeight = minDist[i];
            }
        }
        return index;
    }

    private void add(boolean[] selected, int nodeIndex) {
        selected[nodeIndex] = true;
    }

    /**
     * 判断是否所有顶点都被选中
     *
     * @param selected
     * @return
     */
    private boolean isFinished(boolean[] selected) {
        for (int i = 0; i < selected.length; i++) {
            if (!selected[i]) {
                return false;
            }
        }

        return true;
    }


    /**
     * 复制新的地图
     *
     * @param map 原地图
     * @return 复制版地图
     */
    private int[][] copyMap(int[][] map) {
        int[][] newMap = new int[map.length][map[0].length];
        System.arraycopy(map, 0, newMap, 0, map.length);
        return newMap;
    }

    private void logBooleanArray(boolean[] arr) {
        for (boolean value : arr) {
            System.out.print(value + " ");
        }
        System.out.println(" ");
    }

    private void logIntArray(int[] arr) {
        for (int value : arr) {
            System.out.print(value + " ");
        }
        System.out.println(" ");
    }


    public static void main(String[] args) {
        int max = Integer.MAX_VALUE;
        int[][] map = {
                {max, 4, max, max, max, max, max, 8},
                {4, max, 8, max, max, max, max, 11, max},
                {max, 8, max, 7, max, 4, max, max, 2},
                {max, max, 7, max, 9, 14, max, max, max},
                {max, max, max, 9, max, 10, max, max, max},
                {max, max, 4, 14, 10, max, 2, max, max},
                {max, max, max, max, max, 2, max, 1, 6},
                {8, 11, max, max, max, max, 1, max, 7},
                {max, max, 2, max, max, max, 6, 7, max}
        };

        MinimumSpanningTree minimumSpanningTree = new MinimumSpanningTree(map);
        int[] res = minimumSpanningTree.prim(0);
        for (int i = 0; i < res.length; i++) {
            System.out.println(i + " ~ " + res[i]);
        }


    }
}
