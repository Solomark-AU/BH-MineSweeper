import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class Minesweeper extends JFrame {
private static final int SIZE = 10;
private static final int MINES = 10;
        private static final int CELL_SIZE = 30;

            private final Cell[][] board = new Cell[SIZE][SIZE];//board就系内个。。游戏界面啦 用二维数组对每个格格用于存储游戏板上的单元格
                private final Random random = new Random();

    public Minesweeper() {
        setTitle("fxxking game by Qiuhan ovo");
            setSize(SIZE * CELL_SIZE, SIZE * CELL_SIZE);
                setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    setLocationRelativeTo(null);
                    setLayout(new GridLayout(SIZE, SIZE));

            initializeBoard();
        placeMines();
        calculateNumbers();

        setVisible(true);
    }

    private void initializeBoard() {//如果需要精美gui则需要preitialize和postitialize时间对方法进行注册，此处为初始化当前界面元素（游戏元素）
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                board[row][col] = new Cell(row, col);
                add(board[row][col]);
            }
        }
    }

    private void placeMines() {//随机选择格格并放置地雷，直到放置了MINES个地雷ovo
        int minesPlaced = 0;
        while (minesPlaced < MINES) {
            int row = random.nextInt(SIZE);
            int col = random.nextInt(SIZE);
            if (!board[row][col].isMine()) {
                board[row][col].setMine(true);
                minesPlaced++;
            }
        }
    }

    private void calculateNumbers() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col].isMine()) {
                    continue;
                }
                int mineCount = 0;
                for (int r = row - 1; r <= row + 1; r++) {
                    for (int c = col - 1; c <= col + 1; c++) {
                        if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c].isMine()) {
                            mineCount++;
                        }
                    }
                }
                board[row][col].setNumber(mineCount);
            }
        }
    }

    private void revealCell(int row, int col) {//揭示指定单元格，如果该单元格周围没有地雷，则递归揭示周围的格格
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col].isRevealed()) {
            return;
        }
        board[row][col].reveal();
        if (board[row][col].getNumber() == 0) {
            for (int r = row - 1; r <= row + 1; r++) {
                for (int c = col - 1; c <= col + 1; c++) {
                    revealCell(r, c);
                }
            }
        }
    }

    private boolean checkWin() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!board[row][col].isMine() && !board[row][col].isRevealed()) {//如果递归计算得最后没格子给你揭开了 就赢了
                    return false;
                }
            }
        }
        return true;
    }

    private class Cell extends JButton {//具体单元格的函数们 因为cell有单元的意思而且最近生物在学细胞（
        private final int row;
        private final int col;
        private boolean mine;
        private int number;
        private boolean revealed;
        private boolean flagged;

        public Cell(int row, int col) {
            this.row = row;
            this.col = col;
            this.mine = false;
            this.number = 0;
            this.revealed = false;
            this.flagged = false;

            setPreferredSize(new Dimension(CELL_SIZE, CELL_SIZE));
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {//鼠标监听器 看你点没电右键
                     if (SwingUtilities.isLeftMouseButton(e)) {
                            if (!flagged) {
                                if (mine) {

                                JOptionPane.showMessageDialog(null, "U fxxking loser lol");
                                System.exit(0);
                            } else {
                                revealCell(row, col);
                                if (checkWin()) {
                                    JOptionPane.showMessageDialog(null, "wow youre generous");
                                    System.exit(0);
                                }
                            }
                        }
                    } else if (SwingUtilities.isRightMouseButton(e)) {
                        flagged = !flagged;
                        setText(flagged ? "F" : "");
                    }
                }
            });
        }

        public boolean isMine() {
            return mine;
        }

        public void setMine(boolean mine) {
            this.mine = mine;
        }

        public int getNumber() {
            return number;
        }

        public void setNumber(int number) {
            this.number = number;
        }

        public boolean isRevealed() {
            return revealed;
        }

        public void reveal() {
            revealed = true;
            if (mine) {
                setBackground(Color.RED);
            } else {
                setBackground(Color.LIGHT_GRAY);
                if (number > 0) {
                    setText(String.valueOf(number));
                }
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Minesweeper::new);
    }//EventBus
}