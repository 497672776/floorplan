from matplotlib.lines import Line2D
import matplotlib.pyplot
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

import sys




def drawLayout(plt_title,outline,width,height,x_pos,y_pos):
    #define Matplotlib figure and axis
    fig, ax = plt.subplots()
    plt.title(plt_title) 

    max_y = 0
    max_x = 0
    for i in range(len(width)):
        ax.add_patch(Rectangle((x_pos[i],y_pos[i]),width[i],height[i],edgecolor='pink',fill=True))
        ax.text(x_pos[i]+width[i]/2,y_pos[i]+height[i]/2,i)
        if(x_pos[i]+width[i] > max_x):
            max_x = x_pos[i] + width[i]
        if(y_pos[i]+width[i] > max_y):
            max_y = y_pos[i] + width[i]

    outx,outy = outline

    temp_x = max(max_x,outx)
    temp_y = max(max_y,outy)

    ax.set_xlim(0,max(temp_x,temp_y))
    ax.set_ylim(0,max(temp_x,temp_y))
    ax.add_line(Line2D([outx,outx],[0,outy],linewidth=5,color="red"))
    ax.add_line(Line2D([0,outx],[outy,outy],linewidth=5,color="red"))
    ax.plot()

    #display plot
    plt.savefig(sys.argv[1]+".png")
    plt.show()


if __name__=="__main__":
    layout = open(sys.argv[1],"r")
    outline_x,outline_y = layout.readline().split()
    outline_x = int(outline_x)
    outline_y = int(outline_y)
    blockNum = int(layout.readline())
    print("outline :",outline_x," ",outline_y)
    print("blockNum: ",blockNum)

    title = ""
    title = layout.readline()

    width = []
    height = []
    x_pos = [] 
    y_pos = []
    for i in range(blockNum):
        x,y,w,h = layout.readline().split()   
        width.append(int(w))
        height.append(int(h))
        x_pos.append(int(x))
        y_pos.append(int(y))
    layout.close()
    drawLayout(title,(outline_x,outline_y),width,height,x_pos,y_pos)

