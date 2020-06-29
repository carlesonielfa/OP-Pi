import OLED_Driver as OLED
from PIL  import Image, ImageDraw, ImageFont, ImageColor
from random import uniform
class ScreenManager:
    def __init__(self, op_pi):
        self.op_pi=op_pi
        OLED.Device_Init()
        self.colors = ['RED','#7FFF00','YELLOW','BLUE']
        self.font_sizes = {'huge':30,'big':20,'medium-small': 14,'medium': 16,'small': 10}
        self.fonts = {key:ImageFont.truetype('fonts/ChakraPetch-Regular.ttf',value) for key, value in self.font_sizes.items()}
    def refresh_screen(self):
        image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
        draw = ImageDraw.Draw(image)
        if(self.op_pi.state == 0):
            self.draw_mixer(draw)
        elif(self.op_pi.state == 1):
            self.draw_track_detail(draw, self.op_pi.tracks[0])
        OLED.Display_Image(image)
    def draw_track_detail(self,draw, track):
        self.draw_text(draw, [0,-5], track.name, fill = "WHITE", font = self.fonts['huge'])
        draw.rectangle([28,6,128,22], fill='GRAY')
        fill_percent = track.volume
        draw.rectangle([28,6,28 + 100*track.volume,22], fill=self.colors[0])
        for i,effect in enumerate(track.effects):
            self.draw_effect(draw,32+i*40, effect)
    def draw_effect(self,draw,y,effect):
        outline_color = 'WHITE' if(effect.enabled) else'GRAY'
        draw.rectangle([1,y,128-1,y+30], outline=outline_color)
        self.draw_text(draw, [4,y], effect.__class__.__name__.upper(), fill = outline_color, font = self.fonts['medium-small'])
        for i,parameter in enumerate(effect.parameters):
            s = '{} {:<2}'.format(parameter[0], parameter[1])
            self.draw_text(draw, [8+i*45,y+17], s, fill = self.colors[i+1], font = self.fonts['small'])
    def draw_mixer(self,draw):
        #BPM 
        w,h = self.draw_text(draw, [0,0], str(self.op_pi.bpm), fill = "WHITE", font = self.fonts['medium'], alignH='centered')
        self.draw_text(draw, [0,h], 'BPM', fill = "WHITE", font = self.fonts['small'], alignH='centered')
        rect_w = 29
        rect_h = 29
        draw.rectangle([(OLED.SSD1351_WIDTH - rect_w)/2, 0, (OLED.SSD1351_WIDTH + rect_w)/2, rect_h], outline = "WHITE")
        #TRACKS
        for i, track in enumerate(self.op_pi.tracks):
            self.draw_track(draw, [i%3*50, 40 + (i//3)*((128-40)/3)], track)
    def draw_track(self,draw,cords,track):
        w,h = self.draw_text(draw, cords, track.name, fill="WHITE", font = self.fonts['big'])
        draw.rectangle([cords[0]+25, cords[1]+24, cords[0]+20,cords[1]], fill="GRAY")
        fill_percent = track.volume
        draw.rectangle([cords[0]+25, cords[1]+24, cords[0]+20,cords[1]+(1-fill_percent)*24], fill=self.colors[0])
    def draw_menu(self, draw, options, nselected, x=0, y=0):
        font = self.fonts["medium"]
        for i, option in enumerate(options):
            if(i==nselected):
                draw.rectangle((0, y+i*self.font_sizes["medium"]+4, 128, y+(i+1)*self.font_sizes["medium"]), fill="#FFFF00")
                draw.text((0, y+i*self.font_sizes["medium"]), option, fill = "BLACK", font = font)
            else:
                draw.text((0, y+i*self.font_sizes["medium"]), option, fill = "#FFFF00", font = font)
    def draw_text(self, draw, cords , text, fill, font, anchor=(0,0), alignH='left'):
        w,h = draw.textsize(text, font=font)
        if(alignH=='centered'):
            cords[0] = (OLED.SSD1351_WIDTH - w)/2

        draw.text(cords, text,fill=fill, font = font)
        return w,h
    
    def __del__(self):
        print("Erasing screen")
        OLED.Clear_Screen()
    

