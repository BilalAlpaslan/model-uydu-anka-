from django.urls import path
from . import views


urlpatterns= [
	path('anka/<int:x>/<int:y>/<int:z>',views.anka,name='anka'),
	path('map/<int:a>/<int:b>',views.map,name='map'),
]