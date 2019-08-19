/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.br.phdev.gameeditor;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;

/**
 *
 * @author Paulo Henrique Goncalves Bacelar <henrique.phgb@gmail.com>
 */
public class ImageUpdate {

    private Rectangle rect;
    private Color color;
    private boolean fill;

    public ImageUpdate(Rectangle rect, Color color) {
        this.rect = rect;
        this.color = color;
        this.fill = false;
    }

    public Rectangle getRect() {
        return rect;
    }

    public void setRect(Rectangle rect) {
        this.rect = rect;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public boolean isFill() {
        return fill;
    }

    public void setFill(boolean fill) {
        this.fill = fill;
    }

    public void draw(Graphics2D g) {
        g.setColor(this.color);
        if (fill) {
            g.fillRect(this.rect.x, this.rect.y, this.rect.width, this.rect.height);
        } else {
            g.drawRect(this.rect.x, this.rect.y, this.rect.width, this.rect.height);
        }
    }

}
