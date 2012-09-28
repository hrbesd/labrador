/*
   Author:     yufei
   DateCreated: 2008.08.25
   ======================================

    xmldoc=new JSXML();
    var xmlString='<?xml version="1.0" encoding="utf-8" ?> ...';
    xmldoc.Load('books.xml');//加载XML文件
    xmldoc.LoadXML(xmlString);//加载XML字符串
    xmldoc.ToString();//返回XML文件内容       
    xmldoc.GetAllNode();//返回所有节点(数组)
    xmldoc.GetByName('title');//返回指定标记的节点(数组)
    xmldoc.GetSingleByName('title',index);//返回指定标记的第index个节点
    xmldoc.GetValue(Node);//返回所输入节点的文本值
    xmldoc.GetSingleNode:function(XPath);//返回指定XPath的第1个节点
    xmldoc.CreateNode(Type, NodeName,Text)//创建节点类型为Type, 节点名为NodeName,节点值为Text的节点并返回该节点
    
    xmldoc.XmlDocObj;//属性,返回XML文档对象
    xmldoc.FirstChild;//属性,返回XML文档的第一个节点
    xmldoc.LastChild;//属性,返回XML文档的最后一个节点    
    
    JSXML.isIE;//静态属性,判断浏览器是否为IE
    JSXML.ToString(Node);////静态方法,将指定节点转为字符串
    
*/

function JSXML()
{
    this.XMLDoc=null;
    this.isIE=!!(window.attachEvent && !window.opera);
    this.init();  
}

/*定义实例方法*/
JSXML.prototype={   
    XmlDocObj:null,
    FirstChild:null,
    LastChild:null,
    
    GetXMLDocObj:function()
    {
        return this.XMLDoc;
    },
    
    init:function()
    {
        if(this.isIE) 
        {
            this.XMLDoc=new ActiveXObject("Microsoft.XMLDOM");
        }
        else
        {
            this.XMLDoc=document.implementation.createDocument("","",null);
        }  
        this.XmlDocObj=this.XMLDoc;
        return true;
    },    
    
    Load:function(XMLPath)
    {    
        try 
        {
            this.XMLDoc.async=false;
            this.XMLDoc.load(XMLPath);
            var _allNode=this.GetAllNode();
            this.FirstChild=_allNode[0];
            this.LastChild=_allNode[_allNode.length-1];
            return true;
        }
        catch(e) 
        {
            return false;
        }   
    },
    
    LoadXML:function(XMLString)
    {    
        if(this.isIE) 
        {
            this.XMLDoc.loadXML(XMLString);
        }
        else
        {
            parser=new DOMParser();
            this.XMLDoc=parser.parseFromString(XMLString,"text/xml");
        }  
        var _allNode=this.GetAllNode();
        this.FirstChild=_allNode[0];
        this.LastChild=_allNode[_allNode.length-1];
        return true;
    },
    
    GetAllNode:function()
    {
        if(this.isIE) 
        {
            return this.XMLDoc.documentElement.childNodes;
        }
        else
        {
            return checkNode(this.XMLDoc.documentElement,1);
        }
    },  
      
    GetByName:function(TagName)
    {
        if(arguments.length<=0)
        {
            return this.GetAllNode();
        }
        return this.XMLDoc.getElementsByTagName(TagName);
    },
    
    GetSingleByName:function(TagName,index)
    {
        if(arguments.length<=1)
        {
            index=0;
        }
        var _nodes=this.GetByName(TagName);
        if(index>=_nodes.length)
        {
            return null;
        }
        if(_nodes.length>0)
        {
            return _nodes[index];
        }
        return null;
    },  

    GetValue:function(Node)
    {
        if(Node.childNodes[0].nodeType ==3)
        {
            return Node.childNodes[0].nodeValue;
        }
        else
        {
            return null;
        }
    },
    
    GetSingleNode:function(XPath)
    {
        var _nodeNames=_trim(XPath).split('/');
        var Node=this.XMLDoc;
        for(var i=0;i<_nodeNames.length;i++)    
        {
            Node=Node.getElementsByTagName(_nodeNames[i]); 
            if(Node.length>0)
            {
                Node=Node[0];
            }
        }
        return Node;       
    },
    
    CreateNode:function (Type, NodeName,Text)
    {     
        if(this.isIE) 
        {
            var _node= this.XMLDoc.createNode(Type, NodeName, "");
            _node.appendChild(this.XMLDoc.createTextNode(Text));
            return _node;           
        }   
        else
        {
            return null;
        }
         
    },
     
    ToString:function()
    {       
        return JSXML.ToString(this.XMLDoc.documentElement);
    }
}


JSXML.isIE=!!(window.attachEvent && !window.opera);

JSXML.ToString=function(Node)
{
    if(typeof Node=='string')
    {
        return Node;
    }
    if(JSXML.isIE)
    {
        return Node.xml;
    }
    else
    {
        return serializeXml(Node);
    }
}

function serializeXml(oNode) 
{
    if(oNode)
    {
        var oSerializer = new XMLSerializer();
        return oSerializer.serializeToString(oNode);
    }
    return '';
}

function checkNode(oNode,Type)
{  
    var _arr=new Array();
    for (var i = 0; i < oNode.childNodes.length; i++)
    {
        if (oNode.childNodes[i].nodeType==Type) 
        {
            _arr.push(oNode.childNodes[i]);
        }
    }
    return _arr;
}
function _trim(str)
{
    var reg=new RegExp('^\/');
    var reg2=new  RegExp('\/$');
    return str.replace(reg,"").replace(reg2,"");
}

