# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import sys
import re

# YOUR CODE GOES HERE
# templine=['a "Weber Street" (5,6) (3,8)\n' ,'a "King Street S" (3,2) (4,8)\n','a "Davenport Road" (0,0) (5,8)\n', 'g\n']

def string_to_number(coordinate):  #the coordinate in dictionary is string

    templist=[] #without determining the size of a list, the size will be 1
    res1=re.finditer(r"\-?\d+\.?\d*",coordinate)
    #res1 = re.search(r'\((.*)\)',coordinate)
    #tempcoordinate = res1.groupdict()
    for match in res1:
        templist.append(float(match.group()))
    list=[[0 for col in range(3)]for row in range(len(templist)/2)]
    for k in range(len(templist)):
        i=k%2
        j=k//2
        list[j][i]=templist[k]
    return list 
    #res2=re.search(r'\W(\d{1})\W{1,}(\d{1})')
    
def label(v,value):
    for nn in v.keys():
        if v[nn] == value:
            return nn

def parallel(x1, y1, x2, y2, x3, y3, x4, y4):
    k1 = round((x2-x1) * (y4-y3),2)
    k2 = round((x4-x3) * (y2-y1),2)
    if (k1 == k2):
        return True
    else:
        return False

def onSegment1(x1, y1, x2, y2, x3, y3, x4, y4):
    k1 = round((x3-x1) * (y2-y1),2)
    k2 = round((x2-x1) * (y3-y1),2)
    k3 = round((x4-x1) * (y2-y1),2)
    k4 = round((x2-x1) * (y4-y1),2)
    k5 = round((x1-x3) * (y4-y3),2)
    k6 = round((x4-x3) * (y1-y3),2)
    k7 = round((x2-x3) * (y4-y3),2)
    k8 = round((x4-x3) * (y2-y3),2)
    if (x1==x2==x3==x4 and min(y1,y2)<y3 and max(y1,y2)>y3):
        return True
    elif (x1==x2==x3==x4 and min(y1,y2)<y4 and max(y1,y2)>y4):
        return True
    elif (x1==x2==x3==x4 and min(y3,y4)<y1 and max(y3,y4)>y1):
        return True
    elif (x1==x2==x3==x4 and min(y3,y4)<y2 and max(y3,y4)>y2):
        return True
    elif (y1==y2==y3==y4 and min(x1,x2)<x3 and max(x1,x2)>x3):
        return True
    elif (y1==y2==y3==y4 and min(x1,x2)<x4 and max(x1,x2)>x4):
        return True
    elif (y1==y2==y3==y4 and min(x3,x4)<x1 and max(x3,x4)>x1):
        return True
    elif (y1==y2==y3==y4 and min(x3,x4)<x2 and max(x3,x4)>x2):
        return True
    
    elif (k1 == k2
    and min(x1,x2)<x3 and max(x1,x2)>x3
    and min(y1,y2)<y3 and max(y1,y2)>y3):
        return True
    elif (k3 == k4
    #elif ((x4-x1)*(y2-y1)==(x2-x1)*(y4-y1) 
    and min(x1,x2)<x4 and max(x1,x2)>x4
    and min(y1,y2)<y4 and max(y1,y2)>y4):
        return True
    elif (k5 == k6
    #elif ((x1-x3)*(y4-y3)==(x4-x3)*(y1-y3) 
    and min(x3,x4)<x1 and max(x3,x4)>x1
    and min(y3,y4)<y1 and max(y3,y4)>y1):
        return True
    elif (k7 == k8
    #elif ((x2-x3)*(y4-y3)==(x4-x3)*(y2-y3) 
    and min(x1,x2)<x2 and max(x1,x2)>x2
    and min(y1,y2)<y2 and max(y1,y2)>y2):
        return True
    
    else:
        return False
    

def onSegment(x1, y1, x2, y2, x3, y3):
    k1 = round((x3-x1) * (y2-y1),2)
    k2 = round((x2-x1) * (y3-y1),2)
    if (k1 == k2):
        if (y1==y2==y3):
            if (min(x1,x2)<x3 and max(x1,x2)>x3):
                return True
        elif (x1==x2==x3):
            if (min(y1,y2)<y3 and max(y1,y2)>y3):
                return True
        elif (min(x1,x2)<x3 and max(x1,x2)>x3
        and min(y1,y2)<y3 and max(y1,y2)>y3):
            return True
    
        else:
            return False  
 
def hasSamePoint(list,p1):
    for i in range(len(list)):
        j=0
        if p1[j]==list[i][j]:
            if p1[j+1]==list[i][j+1]:
                return list[i]       
    return False
  
def printVertex(v):
    sys.stdout.write( "V = { " + "\n")
    for key in v:
        vertex=v[key]
        sys.stdout.write(" " + str(key) + ": " + str(vertex) + "\n")
    sys.stdout.write( "}" + "\n")

def printEdge(edges):
    sys.stdout.write( "E = { " + "\n")
    for index in range(len(edges)):
        edge=edges[index]
        sys.stdout.write(" " + str(edge))
        if (index != len(edges)-1):
            sys.stdout.write("," + "\n")
        else:
            sys.stdout.write("\n")     
    sys.stdout.write( "}"  + "\n")       
          
    
def pp(x):
    """Returns a pretty-print string representation of a number.
       A float number is represented by an integer, if it is whole,
       and up to two decimal places if it isn't
    """
    if isinstance(x, float):
        if x.is_integer():
            return str(int(x))
        else:
            return "{0:.2f}".format(x)
    return str(x)

def ppp(x):
    """Returns a pretty-print string representation of a number.
       A float number is represented by an integer, if it is whole,
       and up to 4 decimal places if it isn't
    """
    if isinstance(x, float):
        if x.is_integer():
            return str(int(x))
        else:
            return "{0:.4f}".format(x)
    return str(x)


class point(object):
    """A point in a two dimensional space"""
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        return '(' + pp(self.x) + ', ' + pp(self.y) + ')'
        
    def __eq__(self, other):
        """Override the default Equals behavior"""
        return self.x == other.x and self.y == other.y
    def __ne__(self, other):
        """Override the default Unequal behavior"""
        return self.x != other.x or self.y != other.y

    def __getitem__(self, index):
        if index==0:
            return self.x
        if index==1:
            return self.y
        
    def __cmp__(self, other):
        if self.y == other.y:
            if self.x<other.x:
                return -1
            if self.x == other.x:
                return 0
            else:
                return 1
        if self.y < other.y:
            return -1
        else:
            return 1

class line(object):
    """A line between two points"""
    def __init__(self, src, dst):
        self.src = src
        self.dst = dst

    def __repr__(self):
        #return '['+ str(self.src) + '-->' + str(self.dst) + ']'
        return '<'+ str(self.src) + ',' + str(self.dst) + '>'
    def __eq__(self, other):
        """Override the default Equals behavior"""
        #return self.src == other.src and self.dst == other.dst
        return (self.src == other.src and self.dst == other.dst) or (self.src == other.dst and self.dst == other.src)
    def __ne__(self, other):
        """Override the default Unequal behavior"""
        #return self.src != other.src or self.dst != other.dst
        return (self.src != other.src and self.dst != other.dst) and (self.src != other.dst and self.dst != other.src)
    def __iter__(self):  # 返回迭代器对象本身
        return self

def intersect (l1, l2):
    """Returns a point at which two lines intersect"""
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y

    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    
    xnum = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    t =  xnum / xden

    ynum = ((x1-x2)*(y1-y3) - (y1-y2)*(x1-x3))
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    u = - ynum / yden
      
    xcoor = float(x1+t*(x2-x1))
    ycoor = float(y1+t*(y2-y1))
    if (t>=0 and t<=1 and u>=0 and u<=1):
        return point(xcoor, ycoor)
    else:
        return '0'
    
    
    
def main():
    ### YOUR MAIN CODE GOES HERE
    ### sample code to read from stdin.
    ### make sure to remove all spurious print statements as required
    ### by the assignment
    tempstreetdic=dict()
    streetdic=dict()
    
    while True:
        linestr = sys.stdin.readline()
        #linestr = raw_input()
        #linestr=linestr[:len(linestr)-1]
        if linestr == "":
            sys.exit(0)
            #continue
        
        res1 = re.search(r'(?P<processing>[acrg]{1}).*',linestr)
        #res1 = re.search(r'(?P<processing>[acrg]{1})\W{2,}[\w+]*\s[\w+]*\W{2,}',linestr)
        try:
            tempstreetdic = res1.groupdict()
        except AttributeError:
            sys.stderr.write( "Error: wrong command\n")
            continue
        
        if tempstreetdic['processing']=='g':
            namelist=streetdic.keys()
            #valuelist=streetdic.values()
            valuelist=[]
            streetdic[namelist[0]][0][2]=1
            valuelist.append(streetdic[namelist[0]][0])
            
            #vertices2=dict()
            m=2
            
            len_namelist=len(namelist)
            for i in range(len_namelist):
                for j in range(len(streetdic[namelist[i]])):
                    if hasSamePoint(valuelist,streetdic[namelist[i]][j]):
                        streetdic[namelist[i]][j][2]=hasSamePoint(valuelist,streetdic[namelist[i]][j])[2]
                    else: 
                        valuelist.append(streetdic[namelist[i]][j])
                        streetdic[namelist[i]][j][2]= m
                        m=m+1
                            
            i=0
            j=0
            k=0
            l=0
            v = dict()
            edges = []
            for i in range(len_namelist):
                for j in range(i + 1,len_namelist):
                    for k in range(len(streetdic[namelist[i]])-1):
                        for l in range(len(streetdic[namelist[j]])-1):
                            x1=streetdic[namelist[i]][k][0]
                            y1=streetdic[namelist[i]][k][1]
                            x2=streetdic[namelist[i]][k+1][0]
                            y2=streetdic[namelist[i]][k+1][1]
                            x3=streetdic[namelist[j]][l][0]
                            y3=streetdic[namelist[j]][l][1]
                            x4=streetdic[namelist[j]][l+1][0]
                            y4=streetdic[namelist[j]][l+1][1]
                            l1 = line(point(x1, y1), point(x2, y2))
                            l2 = line(point(x3, y3), point(x4, y4))
                            p1 = point(x1,y1)
                            p2 = point(x2,y2)
                            p3 = point(x3,y3)
                            p4 = point(x4,y4)
                            if parallel(x1, y1, x2, y2, x3, y3, x4, y4):
                                if onSegment1(x1, y1, x2, y2, x3, y3, x4, y4):
                                    if (p1 not in v.values()):
                                        v[int(streetdic[namelist[i]][k][2])] = point(x1,y1)
                                    if (p2 not in v.values()):
                                        v[int(streetdic[namelist[i]][k+1][2])] = point(x2,y2)
                                    if (p3 not in v.values()):  
                                        v[int(streetdic[namelist[j]][l][2])] = point(x3,y3)
                                    if (p4 not in v.values()): 
                                        v[int(streetdic[namelist[j]][l+1][2])] = point(x4,y4)
                                        
                                    if (line(streetdic[namelist[i]][k][2],streetdic[namelist[i]][k+1][2]) not in edges):
                                        if (streetdic[namelist[i]][k][2]!=streetdic[namelist[i]][k+1][2]):
                                            edges.append(line(streetdic[namelist[i]][k][2],streetdic[namelist[i]][k+1][2]))
                                    if (line(streetdic[namelist[j]][l][2],streetdic[namelist[j]][l+1][2]) not in edges):
                                        if (streetdic[namelist[j]][l][2]!=streetdic[namelist[j]][l+1][2]):
                                            edges.append(line(streetdic[namelist[j]][l][2],streetdic[namelist[j]][l+1][2]))
                                continue
                             
                            cur_intersect = intersect(l1, l2)
                            try:
                                if cur_intersect == '0':
                                    continue
                            except AttributeError:
                                pass
                               
                            cur_intersect = [cur_intersect.x, cur_intersect.y]
                    
                            if (p1 not in v.values()):
                                v[int(streetdic[namelist[i]][k][2])] = point(x1,y1)
                            if (p2 not in v.values()):
                                v[int(streetdic[namelist[i]][k+1][2])] = point(x2,y2)
                            if (p3 not in v.values()):  
                                v[int(streetdic[namelist[j]][l][2])] = point(x3,y3)
                            if (p4 not in v.values()): 
                                v[int(streetdic[namelist[j]][l+1][2])] = point(x4,y4)
                           
                            if (intersect(l1, l2) not in v.values()):
                                v[m] = intersect(l1,l2)
                                m=m+1
                                
                                
                        
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][k][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k+1][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][k+1][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k+1][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[j]][l][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l+1][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[j]][l+1][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l+1][2]))
                            else:
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][k][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k+1][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][k+1][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[i]][k+1][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][l][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l][2]))
                                if (line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l+1][2]) not in edges):
                                    if (label(v,intersect(l1, l2))!=streetdic[namelist[i]][l+1][2]):
                                        edges.append(line(label(v,intersect(l1, l2)),streetdic[namelist[j]][l+1][2]))
            

            flag=1
            while(flag==1):
                flag=0
                for ii in range(len(edges)):
                    for jj in range(ii+1,len(edges)):
                        
                        compare1=re.search(r"\W(\d+)\W(\d+)\W",str(edges[ii]))
                        compare2=re.search(r"\W(\d+)\W(\d+)\W",str(edges[jj]))
                        
                        p1=int(compare1.group(1))
                        p2=int(compare1.group(2))
                        p3=int(compare2.group(1))
                        p4=int(compare2.group(2))
                        
                        pp1=v[p1]
                        pp2=v[p2]
                        pp3=v[p3]
                        pp4=v[p4]
                      
                        if (parallel(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)):
                            if (pp1 in [pp3,pp4]):  
                                if (onSegment(pp3.x, pp3.y, pp4.x, pp4.y, pp2.x, pp2.y)):
                                    if ii<jj:
                                        del edges[ii]
                                        del edges[jj-1]
                                    if ii>jj:
                                        del edges[ii]
                                        del edges[jj]
                                    if (line(label(v,pp2),label(v,pp3)) not in edges):
                                        if (label(v,pp2)!=label(v,pp3)):
                                            edges.append(line(label(v,pp2),label(v,pp3)))
                                    if (line(label(v,pp2),label(v,pp4)) not in edges):
                                        if (label(v,pp2)!=label(v,pp4)):
                                            edges.append(line(label(v,pp2),label(v,pp4)))
                                    
                                    flag=1
                                    break
                                    
                                
                        if (parallel(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)):
                            if (pp2 in [pp3,pp4]):  
                                if (onSegment(pp3.x, pp3.y, pp4.x, pp4.y, pp1.x, pp1.y)):
                                    if ii<jj:
                                        del edges[ii]
                                        del edges[jj-1]
                                    if ii>jj:
                                        del edges[ii]
                                        del edges[jj]
                                    if (line(label(v,pp1),label(v,pp3)) not in edges):
                                        if (label(v,pp1)!=label(v,pp3)):
                                            edges.append(line(label(v,pp1),label(v,pp3)))
                                    if (line(label(v,pp1),label(v,pp4)) not in edges):
                                        if (label(v,pp1)!=label(v,pp4)):
                                            edges.append(line(label(v,pp1),label(v,pp4)))
                                 
                                    flag=1
                                    break
                                    
                                
                        if (parallel(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)):
                            if (pp3 in [pp1,pp2]):  
                                if (onSegment(pp1.x, pp1.y, pp2.x, pp2.y, pp4.x, pp4.y)):
                                    if ii<jj:
                                        del edges[ii]
                                        del edges[jj-1]
                                    if ii>jj:
                                        del edges[ii]
                                        del edges[jj]
                                    if (line(label(v,pp4),label(v,pp1)) not in edges):
                                        if (label(v,pp4)!=label(v,pp1)):
                                            edges.append(line(label(v,pp4),label(v,pp1)))
                                    if (line(label(v,pp4),label(v,pp2)) not in edges):
                                        if (label(v,pp4)!=label(v,pp2)):
                                            edges.append(line(label(v,pp4),label(v,pp2)))
       
                                    flag=1
                                    break
                                
                        if (parallel(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)):
                            if (pp4 in [pp1,pp2]):  
                                if (onSegment(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y)):
                                    if ii<jj:
                                        del edges[ii]
                                        del edges[jj-1]
                                    if ii>jj:
                                        del edges[ii]
                                        del edges[jj]
                                    if (line(label(v,pp3),label(v,pp1)) not in edges):
                                        if (label(v,pp3)!=label(v,pp1)):
                                            edges.append(line(label(v,pp3),label(v,pp1)))
                                    if (line(label(v,pp3),label(v,pp2)) not in edges):
                                        if (label(v,pp3)!=label(v,pp2)):
                                            edges.append(line(label(v,pp3),label(v,pp2)))
                                
                                    flag=1
                                    break
                        
                            
                        if (onSegment1(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)): 
                            if (parallel(pp1.x, pp1.y, pp2.x, pp2.y, pp3.x, pp3.y, pp4.x, pp4.y)):
                            
                                cur_edges=[pp1, pp2, pp3, pp4]
                                cur_edges2=sorted(cur_edges, key=lambda x:(x[0],x[1]))
                                if ii<jj:
                                    del edges[ii]
                                    del edges[jj-1]
                                if ii>jj:
                                    del edges[ii]
                                    del edges[jj]
                                if (line(label(v,cur_edges2[0]),label(v,cur_edges2[1])) not in edges):
                                    if ((v,cur_edges2[0])!=label(v,cur_edges2[1])):
                                        edges.append(line(label(v,cur_edges2[0]),label(v,cur_edges2[1])))
                                if (line(label(v,cur_edges2[1]),label(v,cur_edges2[2])) not in edges):
                                    if ((v,cur_edges2[1])!=label(v,cur_edges2[2])):
                                        edges.append(line(label(v,cur_edges2[1]),label(v,cur_edges2[2])))
                                if (line(label(v,cur_edges2[2]),label(v,cur_edges2[3])) not in edges):
                                    if ((v,cur_edges2[2])!=label(v,cur_edges2[3])):
                                        edges.append(line(label(v,cur_edges2[2]),label(v,cur_edges2[3])))
                                
                                flag=1
                                break
                    if flag==1:
                        break
                
                     
            
            printVertex(v)
            printEdge(edges)
            
        
           
        else:
            res1 = re.search(r'(?P<processing>[acrg]{1})\s{1,}\"{1}(?P<name>\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*)\"',linestr)
            #tempstreetdic = res1.groupdict()
            try:
                tempstreetdic = res1.groupdict()
            except AttributeError:
                sys.stderr.write( "Error: wrong command\n")
                continue
            
            if tempstreetdic['processing']=='a':
                #need to determine if the street is in the dictionary
                if streetdic.has_key(str(tempstreetdic['name']).lower()):
                    sys.stderr.write( "Error: this street has existed\n")
                else:
                    res1 = re.search(r'(?P<processing>[acrg]{1})\s{1,}\"{1}(?P<name>\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*)\W{2,}(?P<coordinate>\(.{8,}\))',linestr)
                    try:
                        tempstreetdic = res1.groupdict()
                        streetdic[str(tempstreetdic['name']).lower()]=string_to_number(tempstreetdic['coordinate'])
                    except AttributeError:
                        sys.stderr.write( "Error: wrong coordinate\n")
                        continue
                    
            elif tempstreetdic['processing']=='c':
                #need to determine if the street is in the dictionary
                if streetdic.has_key(str(tempstreetdic['name']).lower()):
                    res1 = re.search(r'(?P<processing>[acrg]{1})\W{2,}(?P<name>\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*\s*[A-Za-z+]*)\W{2,}(?P<coordinate>\(.{8,}\))',linestr)
                    try:
                        tempstreetdic = res1.groupdict()
                        streetdic[str(tempstreetdic['name']).lower()]=string_to_number(tempstreetdic['coordinate'])
                    except AttributeError:
                        sys.stderr.write( "Error: wrong coordinate\n")
                        continue
                else:
                    sys.stderr.write( "Error: this street do not exist\n" )
                
            elif tempstreetdic['processing']=='r':
                #need to determine if the street is in the dictionary
                if streetdic.has_key(str(tempstreetdic['name']).lower()):
                    del streetdic[str(tempstreetdic['name']).lower()];
                else:
                   sys.stderr.write( "Error: this street do not exist\n" )
                   
            else:
                sys.stderr.write( "Error: wrong command\n" )
                    

if __name__ == '__main__':
    main()
    
    