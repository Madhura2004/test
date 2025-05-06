import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

class Node 
{
    Node parent;
    int[][] board;
    int x, y, g, h;

    Node(int[][] board, int x, int y, int g, int h, Node parent) 
    {
        this.board = new int[3][3];
        for (int i = 0; i < 3; i++)
            System.arraycopy(board[i], 0, this.board[i], 0, 3);
        this.x = x;
        this.y = y;
        this.g = g;
        this.h = h;
        this.parent = parent;
    }
}

public class Astar 
{
    static final int N = 3;
    static final int[] dRow = {1, 0, -1, 0};
    static final int[] dCol = {0, -1, 0, 1};

    static void printBoard(int[][] board, int g, int h) 
    {
        for (int[] row : board) 
        {
            for (int val : row) System.out.print(val + " ");
            System.out.println();
        }
        System.out.println("g: " + g + " h: " + h + " f: " + (g + h) + "\n");
    }

    static void printPath(Node node) 
    {
        if (node == null) 
        {
            return;
        }
        printPath(node.parent);
        printBoard(node.board, node.g, node.h);
    }

    static boolean isValid(int x, int y) 
    {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    static int calcHeuristic(int[][] current, int[][] goal) 
    {
        int mismatches = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (current[i][j] != 0 && current[i][j] != goal[i][j])
                    mismatches++;
        return mismatches;
    }

    static Node createNode(int[][] board, int x, int y, int newX, int newY, int g, Node parent) 
    {
        Node node = new Node(board, newX, newY, g, 0, parent);
        int temp = node.board[x][y];
        node.board[x][y] = node.board[newX][newY];
        node.board[newX][newY] = temp;
        return node;
    }

    static boolean isSolvable(int[][] start, int[][] goal) 
    {
        int[] startFlat = new int[N * N], goalFlat = new int[N * N];
        int k = 0;
        for (int[] row : start)
            for (int val : row) 
                startFlat[k++] = val;
        k = 0;
        for (int[] row : goal)
            for (int val : row) 
                goalFlat[k++] = val;

        int[] pos = new int[N * N];
        for (int i = 0; i < N * N; i++)
            pos[goalFlat[i]] = i;

        int[] mapped = new int[N * N];
        for (int i = 0; i < N * N; i++)
            mapped[i] = pos[startFlat[i]];

        int inversions = 0;
        for (int i = 0; i < N * N; i++)
            for (int j = i + 1; j < N * N; j++)
                if (mapped[i] > mapped[j] && mapped[j] != 0) inversions++;

        return inversions % 2 == 0;
    }

    public static void main(String[] args) throws FileNotFoundException 
    {
        Scanner sc = new Scanner(new File("puzzle_input.txt"));
        int[][] start = new int[N][N], goal = new int[N][N];
        int sx = -1, sy = -1;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) 
            {
                start[i][j] = sc.nextInt();
                if (start[i][j] == 0) 
                { 
                    sx = i; 
                    sy = j; 
                }
            }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                goal[i][j] = sc.nextInt();

        if (!isSolvable(start, goal)) 
        {
            System.out.println("This puzzle is not solvable.");
            return;
        }

        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(n -> n.g + n.h));
        Node root = new Node(start, sx, sy, 0, calcHeuristic(start, goal), null);
        pq.add(root);

        while (!pq.isEmpty()) 
        {
            Node current = pq.poll();
            if (calcHeuristic(current.board, goal) == 0) 
            {
                printPath(current);
                return;
            }

            for (int i = 0; i < 4; i++) 
            {
                int newX = current.x + dRow[i];
                int newY = current.y + dCol[i];
                if (isValid(newX, newY)) 
                {
                    Node child = createNode(current.board, current.x, current.y, newX, newY, current.g + 1, current);
                    child.h = calcHeuristic(child.board, goal);
                    pq.add(child);
                }
            }
        }

        System.out.println("No solution found.");
    }
}
