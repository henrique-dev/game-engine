/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.br.phdev.gameeditor;

import com.br.phdev.gameeditor.filepick.ImageFileView;
import com.br.phdev.gameeditor.filepick.ImageFilter;
import com.br.phdev.gameeditor.filepick.ImagePreview;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JPopupMenu;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author Paulo Henrique Goncalves Bacelar <henrique.phgb@gmail.com>
 */
public class TextureMapWindow extends javax.swing.JFrame {

    private JFileChooser fc;
    private File fileImage;
    private BufferedImage originalImage;
    private BufferedImage resizedImage;
    private Graphics2D imageFrame;
    private List<ImageUpdate> imageUpdatesGrid;
    private float zoom = 1;
    private int rows = 1, cols = 1;
    private List<Sprite> sprites;

    /**
     * Creates new form TextureMapWindow
     */
    public TextureMapWindow() {
        initComponents();
        centerWindow();

        this.imageUpdatesGrid = new ArrayList<>();
        this.sprites = new ArrayList<>();
    }

    private void centerWindow() {
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width / 2 - this.getSize().width / 2, dim.height / 2 - this.getSize().height / 2);

        DefaultTableModel tableModel = new DefaultTableModel();
        tableModel.setColumnIdentifiers(new String[]{"Nome", "x", "y", "largura", "altura"});
        jTable1.setModel(tableModel);
    }

    private BufferedImage resize(BufferedImage img, int width, int height) {
        Image tmp = img.getScaledInstance(width, height, Image.SCALE_FAST);
        BufferedImage resized = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = resized.createGraphics();
        g2d.drawImage(tmp, 0, 0, null);
        g2d.dispose();
        return resized;
    }

    private void reloadImage() {
        this.label_image.setIcon(null);
        this.resizedImage = resize(this.originalImage, (int) (this.originalImage.getWidth() * zoom), (int) (this.originalImage.getHeight() * zoom));
        this.imageFrame = this.resizedImage.createGraphics();

        if (this.rows > 1 || this.cols > 1) {
            int divW = this.resizedImage.getWidth() / cols;
            int divH = this.resizedImage.getHeight() / rows;
            Color color = new Color(150, 0, 0, 100);
            this.imageUpdatesGrid.clear();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    Rectangle rectangle = new Rectangle(j * divW, i * divH, divW, divH);
                    this.imageUpdatesGrid.add(new ImageUpdate(rectangle, color));
                }
            }
        }

        analisyImageForSprites();

        for (ImageUpdate iu : this.imageUpdatesGrid) {
            iu.draw(imageFrame);
        }

        DefaultTableModel tableModel = new DefaultTableModel();
        tableModel.setColumnIdentifiers(new String[]{"Nome", "x", "y", "largura", "altura"});

        for (Sprite s : sprites) {
            Rectangle rect = new Rectangle(
                    (int) (((float) this.resizedImage.getWidth() / (float) this.originalImage.getWidth()) * s.getRectangle().x),
                    (int) ((float) (this.resizedImage.getHeight() / (float) this.originalImage.getHeight()) * s.getRectangle().y),
                    (int) ((float) (this.resizedImage.getWidth() / (float) this.originalImage.getWidth()) * s.getRectangle().width),
                    (int) ((float) (this.resizedImage.getHeight() / (float) this.originalImage.getHeight()) * s.getRectangle().height));
            s.setRectangleToDraw(rect);
            s.draw(imageFrame);
            tableModel.addRow(new String[]{"sem_nome", String.valueOf(s.getRectangle().x), String.valueOf(s.getRectangle().y),
                String.valueOf(s.getRectangle().width), String.valueOf(s.getRectangle().height)});
        }

        jTable1.setModel(tableModel);

        ImageIcon image = new ImageIcon(this.resizedImage);
        this.label_image.setIcon(image);
    }

    private void analisyImageForSprites() {

        final byte[] pixels = ((DataBufferByte) this.originalImage.getRaster().getDataBuffer()).getData();
        final int width = this.originalImage.getWidth();
        final int height = this.originalImage.getHeight();
        final boolean hasAlphaChannel = this.originalImage.getAlphaRaster() != null;

        int[][] imageRGB = new int[height][width];
        if (hasAlphaChannel) {
            final int pixelLength = 4;
            for (int pixel = 0, row = 0, col = 0; pixel + 3 < pixels.length; pixel += pixelLength) {
                int argb = 0;
                argb += (((int) pixels[pixel] & 0xff) << 24); // alpha
                argb += ((int) pixels[pixel + 1] & 0xff); // blue
                argb += (((int) pixels[pixel + 2] & 0xff) << 8); // green
                argb += (((int) pixels[pixel + 3] & 0xff) << 16); // red
                imageRGB[row][col] = argb;
                col++;
                if (col == width) {
                    col = 0;
                    row++;
                }
            }
        } else {
            final int pixelLength = 3;
            for (int pixel = 0, row = 0, col = 0; pixel + 2 < pixels.length; pixel += pixelLength) {
                int argb = 0;
                argb += -16777216; // 255 alpha
                argb += ((int) pixels[pixel] & 0xff); // blue
                argb += (((int) pixels[pixel + 1] & 0xff) << 8); // green
                argb += (((int) pixels[pixel + 2] & 0xff) << 16); // red
                imageRGB[row][col] = argb;
                col++;
                if (col == width) {
                    col = 0;
                    row++;
                }
            }
        }

        List<List<Rectangle>> rectList = new ArrayList<>();
        for (ImageUpdate iu : this.imageUpdatesGrid) {
            Rectangle rect = new Rectangle(
                    (int) (((float) this.originalImage.getWidth() / (float) this.resizedImage.getWidth()) * iu.getRect().x),
                    (int) ((float) (this.originalImage.getHeight() / (float) this.resizedImage.getHeight()) * iu.getRect().y),
                    (int) ((float) (this.originalImage.getWidth() / (float) this.resizedImage.getWidth()) * iu.getRect().width),
                    (int) ((float) (this.originalImage.getHeight() / (float) this.resizedImage.getHeight()) * iu.getRect().height));

            for (int i = rect.y; i < rect.y + rect.height; i++) {
                int rgb = 0;
                for (int j = rect.x; j < rect.x + rect.width; j++) {
                    rgb = imageRGB[i][j];
                    if (rgb != 0) {
                        break;
                    }
                }
                if (rgb != 0) {
                    iu.setFill(true);
                    boolean intersect = false;
                    for (List<Rectangle> lr : rectList) {
                        for (Rectangle r : lr) {
                            Rectangle recExp = new Rectangle(rect.x - 1, rect.y - 1, rect.width + 2, rect.height + 2);
                            if (r.intersects(recExp)) {
                                intersect = true;
                                break;
                            }
                        }
                        if (intersect) {
                            lr.add(rect);
                            break;
                        }
                    }
                    if (!intersect) {
                        List<Rectangle> recs = new ArrayList<>();
                        recs.add(rect);
                        rectList.add(recs);
                    }
                    break;
                }
            }
        }

        this.sprites.clear();        
        
        for (List<Rectangle> lr : rectList) {
            int left = 0, top = 0, right = 0, bottom = 0;
            boolean first = true;
            for (Rectangle r : lr) {
                if (first) {
                    left = r.x;
                    top = r.y;
                    right = r.x + r.width;
                    bottom = r.y + r.height;
                    first = false;
                }
                if (r.x < left) {
                    left = r.x;
                }
                if (r.y < top) {
                    top = r.y;
                }
                if (r.x + r.width > right) {
                    right = r.x + r.width;
                }
                if (r.y + r.height > bottom) {
                    bottom = r.y + r.height;
                }
            }
            Sprite sprite = new Sprite();
            sprite.setRectangle(new Rectangle(left, top, right - left, bottom - top));
            Random rand = new Random();
            sprite.setColor(new Color(rand.nextInt(250), rand.nextInt(250), rand.nextInt(250), 150));
            sprites.add(sprite);
        }
        
        for (int i=0; i<sprites.size(); i++) { 
            Rectangle a = sprites.get(i).getRectangle();
            for (int j=i+1; j<sprites.size(); j++) {
                Rectangle b = sprites.get(j).getRectangle();
                if (a.getWidth() * a.getHeight() > b.getWidth() * b.getHeight()) {
                    if (a.intersects(b)) {
                        sprites.remove(j);
                        j--;
                        System.out.println("HERE2");
                    }
                } else {
                    if (b.intersects(a)) {
                        sprites.remove(j);
                        j--;
                        System.out.println("HERE2");
                    }
                }
                
            }            
        }

    }

    Dimension getScaledDimension(Dimension imageSize, Dimension boundary) {

        double widthRatio = boundary.getWidth() / imageSize.getWidth();
        double heightRatio = boundary.getHeight() / imageSize.getHeight();
        double ratio = Math.min(widthRatio, heightRatio);

        return new Dimension((int) (imageSize.width * ratio), (int) (imageSize.height * ratio));
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jSplitPane1 = new javax.swing.JSplitPane();
        jPanel4 = new javax.swing.JPanel();
        jPanel2 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jButton2 = new javax.swing.JButton();
        jCheckBox1 = new javax.swing.JCheckBox();
        jPanel9 = new javax.swing.JPanel();
        jButton6 = new javax.swing.JButton();
        textField_rows = new javax.swing.JTextField();
        jButton5 = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        textField_cols = new javax.swing.JTextField();
        jButton7 = new javax.swing.JButton();
        jButton8 = new javax.swing.JButton();
        jSplitPane2 = new javax.swing.JSplitPane();
        jPanel5 = new javax.swing.JPanel();
        jPanel3 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        label_image = new javax.swing.JLabel();
        jPanel6 = new javax.swing.JPanel();
        jButton3 = new javax.swing.JButton();
        jButton4 = new javax.swing.JButton();
        jPanel8 = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();
        jPanel7 = new javax.swing.JPanel();
        jButton1 = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addComponentListener(new java.awt.event.ComponentAdapter() {
            public void componentResized(java.awt.event.ComponentEvent evt) {
                formComponentResized(evt);
            }
        });

        jPanel2.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        jLabel1.setText("Quantidade de linhas:");

        jLabel2.setText("Quantidade de colunas:");

        jButton2.setText("Gerar");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });

        jCheckBox1.setText("Quadradondar");

        jPanel9.setLayout(new java.awt.BorderLayout());

        jButton6.setText("+");
        jButton6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton6ActionPerformed(evt);
            }
        });
        jPanel9.add(jButton6, java.awt.BorderLayout.LINE_END);

        textField_rows.setText("2");
        jPanel9.add(textField_rows, java.awt.BorderLayout.CENTER);

        jButton5.setText("-");
        jButton5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton5ActionPerformed(evt);
            }
        });
        jPanel9.add(jButton5, java.awt.BorderLayout.LINE_START);

        jPanel1.setLayout(new java.awt.BorderLayout());

        textField_cols.setText("24");
        jPanel1.add(textField_cols, java.awt.BorderLayout.CENTER);

        jButton7.setText("-");
        jButton7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton7ActionPerformed(evt);
            }
        });
        jPanel1.add(jButton7, java.awt.BorderLayout.LINE_START);

        jButton8.setText("+");
        jButton8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton8ActionPerformed(evt);
            }
        });
        jPanel1.add(jButton8, java.awt.BorderLayout.LINE_END);

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel9, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jLabel2, javax.swing.GroupLayout.DEFAULT_SIZE, 257, Short.MAX_VALUE)
                    .addComponent(jButton2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jCheckBox1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jLabel2)
                .addGap(7, 7, 7)
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(jCheckBox1)
                .addGap(18, 18, 18)
                .addComponent(jButton2)
                .addContainerGap(276, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout jPanel4Layout = new javax.swing.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel4Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel4Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        jSplitPane1.setLeftComponent(jPanel4);

        jSplitPane2.setDividerLocation(900);
        jSplitPane2.setResizeWeight(0.8);

        jPanel3.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        label_image.setBackground(new java.awt.Color(153, 153, 153));
        label_image.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        label_image.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        label_image.setOpaque(true);
        label_image.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                label_imageMouseClicked(evt);
            }
        });
        label_image.addComponentListener(new java.awt.event.ComponentAdapter() {
            public void componentResized(java.awt.event.ComponentEvent evt) {
                label_imageComponentResized(evt);
            }
        });
        jScrollPane1.setViewportView(label_image);

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1)
                .addContainerGap())
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 383, Short.MAX_VALUE)
                .addContainerGap())
        );

        jPanel6.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        jButton3.setText("Zoom-");
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });

        jButton4.setText("Zoom+");
        jButton4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton4ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel6Layout = new javax.swing.GroupLayout(jPanel6);
        jPanel6.setLayout(jPanel6Layout);
        jPanel6Layout.setHorizontalGroup(
            jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel6Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jButton3)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jButton4)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel6Layout.setVerticalGroup(
            jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel6Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jButton3)
                    .addComponent(jButton4))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout jPanel5Layout = new javax.swing.GroupLayout(jPanel5);
        jPanel5.setLayout(jPanel5Layout);
        jPanel5Layout.setHorizontalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel5Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel6, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanel5Layout.setVerticalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel5Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        jSplitPane2.setLeftComponent(jPanel5);

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jScrollPane2.setViewportView(jTable1);

        javax.swing.GroupLayout jPanel8Layout = new javax.swing.GroupLayout(jPanel8);
        jPanel8.setLayout(jPanel8Layout);
        jPanel8Layout.setHorizontalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 23, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanel8Layout.setVerticalGroup(
            jPanel8Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel8Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 464, Short.MAX_VALUE)
                .addContainerGap())
        );

        jSplitPane2.setRightComponent(jPanel8);

        jSplitPane1.setRightComponent(jSplitPane2);

        jPanel7.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        jButton1.setText("Carregar textura");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel7Layout = new javax.swing.GroupLayout(jPanel7);
        jPanel7.setLayout(jPanel7Layout);
        jPanel7Layout.setHorizontalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel7Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 139, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel7Layout.setVerticalGroup(
            jPanel7Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel7Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jButton1)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jSplitPane1)
                    .addComponent(jPanel7, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel7, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSplitPane1)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        if (fc == null) {
            fc = new JFileChooser();
            fc.addChoosableFileFilter(new ImageFilter());
            fc.setAcceptAllFileFilterUsed(false);
            fc.setFileView(new ImageFileView());
            fc.setAccessory(new ImagePreview(fc));
        }
        int returnVal = fc.showDialog(this, "Attach");
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            try {
                this.fileImage = fc.getSelectedFile();
                this.originalImage = ImageIO.read(this.fileImage);
                reloadImage();
            } catch (Exception e) {

            }
        } else {

        }

        //Reset the file chooser for the next time it's shown.
        fc.setSelectedFile(null);
    }//GEN-LAST:event_jButton1ActionPerformed

    private void formComponentResized(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_formComponentResized

    }//GEN-LAST:event_formComponentResized

    private void label_imageComponentResized(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_label_imageComponentResized

    }//GEN-LAST:event_label_imageComponentResized

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed
        this.rows = Integer.parseInt(this.textField_rows.getText());
        this.cols = Integer.parseInt(this.textField_cols.getText());
        if (this.resizedImage.getWidth() % cols == 0) {
            textField_cols.setBackground(Color.GREEN);
        } else {
            textField_cols.setBackground(Color.RED);
        }
        if (this.resizedImage.getHeight() % rows == 0) {
            textField_rows.setBackground(Color.GREEN);
        } else {
            textField_rows.setBackground(Color.RED);
        }
        reloadImage();
    }//GEN-LAST:event_jButton2ActionPerformed

    private void jButton4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton4ActionPerformed
        this.zoom += 0.5;
        reloadImage();
    }//GEN-LAST:event_jButton4ActionPerformed

    private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton3ActionPerformed
        this.zoom -= 0.5;
        reloadImage();
    }//GEN-LAST:event_jButton3ActionPerformed

    private void label_imageMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_label_imageMouseClicked
        JPopupMenu menu = new JPopupMenu();
        menu.add("A");
        menu.add("B");
        menu.add("C");
        System.out.println(evt.getX() + " - " + evt.getY());
        menu.show(label_image, evt.getX(), evt.getY());
    }//GEN-LAST:event_label_imageMouseClicked

    private void jButton6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton6ActionPerformed
        int tmpRows = Integer.parseInt(textField_rows.getText()) + 1;
        while (this.resizedImage.getHeight() % tmpRows != 0) {
            if (tmpRows > this.resizedImage.getHeight()) {
                break;
            }
            tmpRows++;
        }
        textField_rows.setText(String.valueOf(tmpRows));
    }//GEN-LAST:event_jButton6ActionPerformed

    private void jButton8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton8ActionPerformed
        int tmpCols = Integer.parseInt(textField_cols.getText()) + 1;
        while (this.resizedImage.getWidth() % tmpCols != 0) {
            if (tmpCols > this.resizedImage.getWidth()) {
                break;
            }
            tmpCols++;
        }
        textField_cols.setText(String.valueOf(tmpCols));
    }//GEN-LAST:event_jButton8ActionPerformed

    private void jButton5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton5ActionPerformed
        int tmpRows = Integer.parseInt(textField_rows.getText()) - 1;
        if (tmpRows == 0) {
            tmpRows = 1;
        }
        while (this.resizedImage.getHeight() % tmpRows != 0) {
            if (tmpRows < 2) {
                tmpRows = 1;
                break;
            }
            tmpRows--;
        }
        textField_rows.setText(String.valueOf(tmpRows));
    }//GEN-LAST:event_jButton5ActionPerformed

    private void jButton7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        int tmpCols = Integer.parseInt(textField_cols.getText()) - 1;
        if (tmpCols == 0) {
            tmpCols = 1;
        }
        while (this.resizedImage.getWidth() % tmpCols != 0) {
            if (tmpCols < 2) {
                tmpCols = 1;
                break;
            }
            tmpCols--;
        }
        textField_cols.setText(String.valueOf(tmpCols));
    }//GEN-LAST:event_jButton7ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(TextureMapWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(TextureMapWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(TextureMapWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(TextureMapWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new TextureMapWindow().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JButton jButton3;
    private javax.swing.JButton jButton4;
    private javax.swing.JButton jButton5;
    private javax.swing.JButton jButton6;
    private javax.swing.JButton jButton7;
    private javax.swing.JButton jButton8;
    private javax.swing.JCheckBox jCheckBox1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    private javax.swing.JPanel jPanel7;
    private javax.swing.JPanel jPanel8;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JSplitPane jSplitPane2;
    private javax.swing.JTable jTable1;
    private javax.swing.JLabel label_image;
    private javax.swing.JTextField textField_cols;
    private javax.swing.JTextField textField_rows;
    // End of variables declaration//GEN-END:variables
}
