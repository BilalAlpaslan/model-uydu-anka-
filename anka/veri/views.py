from django.shortcuts import render


def anka(request,x,y,z):
    context={
        'x': x,
        'y': y,
        'z': z,
    }
    return render(request, 'anka.html', context)

def map(request,a,b):
    context={
        'a': a,
        'b': b,
    }
    return render(request, 'map.html', context)