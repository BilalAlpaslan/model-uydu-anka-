from PyQt5.QtWidgets import*

from matplotlib.backends.backend_qt5agg import FigureCanvas
from matplotlib.figure import Figure

    
class MplWidget(QWidget):
    
    def __init__(self, parent = None):

        QWidget.__init__(self, parent)
        
        self.canvas = FigureCanvas(Figure(figsize=(4, 5), dpi=80))
        
        # vertical_layout = QVBoxLayout()
        vertical_layout = QGridLayout()
        vertical_layout.addWidget(self.canvas)
        
        self.canvas.axes = self.canvas.figure.add_subplot(111)
        self.setLayout(vertical_layout)


# 3 boyutlu

# from PyQt5.QtWidgets import*

# from matplotlib.backends.backend_qt5agg import FigureCanvas
# from matplotlib.figure import Figure

    
# class MplWidget3d(QWidget):
    
#     def __init__(self, parent = None):

#         QWidget.__init__(self, parent)
        
#         self.canvas = FigureCanvas(Figure())
        
#         # vertical_layout = QVBoxLayout()
#         vertical_layout = QGridLayout()
#         vertical_layout.addWidget(self.canvas)
        
#         self.canvas.axes = self.canvas.figure.add_subplot(111,projection='3d')
#         # self.canvas.axes.view_init(90, -90)
#         self.setLayout(vertical_layout)
