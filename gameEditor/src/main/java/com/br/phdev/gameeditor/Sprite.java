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
public class Sprite {

    private String texture;
    private String name;
    private Rectangle rectangle;
    private Rectangle rectangleToDraw;

    public String getTexture() {
        return texture;
    }

    public void setTexture(String texture) {
        this.texture = texture;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Rectangle getRectangle() {
        return rectangle;
    }

    public void setRectangle(Rectangle rectangle) {
        this.rectangle = rectangle;
    }

    public Rectangle getRectangleToDraw() {
        return rectangleToDraw;
    }

    public void setRectangleToDraw(Rectangle rectangleToDraw) {
        this.rectangleToDraw = rectangleToDraw;
    }
    
    public void draw(Graphics2D g) {
        g.setColor(new Color(0, 150, 0, 100));
        g.fillRect(this.rectangleToDraw.x, this.rectangleToDraw.y, this.rectangleToDraw.width, this.rectangleToDraw.height);
    }

}
