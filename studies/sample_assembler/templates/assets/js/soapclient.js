/*****************************************************************************\

 Simpler soap client

 @Author: Void Main
 
\*****************************************************************************/

function SOAPClientParameters()
{
    var _pl = new Array();
    this.add = function(name, value) 
    {
        _pl[name] = value; 
        return this; 
    }
    this.toXml = function()
    {
        var xml = "";
        for(var p in _pl)
        {
            switch(typeof(_pl[p])) 
            {
                case "string":
                case "number":
                case "boolean":
                case "object":
                    xml += "<" + p + ">" + SOAPClientParameters._serialize(_pl[p]) + "</" + p + ">";
                    break;
                default:
                    break;
            }
        }
        return xml; 
    }
}
SOAPClientParameters._serialize = function(o)
{
    var s = "";
    switch(typeof(o))
    {
        case "string":
            s += o.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;"); break;
        case "number":
        case "boolean":
            s += o.toString(); break;
        case "object":
            // Date
            if(o.constructor.toString().indexOf("function Date()") > -1)
            {
        
                var year = o.getFullYear().toString();
                var month = (o.getMonth() + 1).toString(); month = (month.length == 1) ? "0" + month : month;
                var date = o.getDate().toString(); date = (date.length == 1) ? "0" + date : date;
                var hours = o.getHours().toString(); hours = (hours.length == 1) ? "0" + hours : hours;
                var minutes = o.getMinutes().toString(); minutes = (minutes.length == 1) ? "0" + minutes : minutes;
                var seconds = o.getSeconds().toString(); seconds = (seconds.length == 1) ? "0" + seconds : seconds;
                var milliseconds = o.getMilliseconds().toString();
                var tzminutes = Math.abs(o.getTimezoneOffset());
                var tzhours = 0;
                while(tzminutes >= 60)
                {
                    tzhours++;
                    tzminutes -= 60;
                }
                tzminutes = (tzminutes.toString().length == 1) ? "0" + tzminutes.toString() : tzminutes.toString();
                tzhours = (tzhours.toString().length == 1) ? "0" + tzhours.toString() : tzhours.toString();
                var timezone = ((o.getTimezoneOffset() < 0) ? "+" : "-") + tzhours + ":" + tzminutes;
                s += year + "-" + month + "-" + date + "T" + hours + ":" + minutes + ":" + seconds + "." + milliseconds + timezone;
            }
            // Array
            else if(o.constructor.toString().indexOf("function Array()") > -1)
            {
                for(var p in o)
                {
                    if(!isNaN(p))   // linear array
                    {
                        (/function\s+(\w*)\s*\(/ig).exec(o[p].constructor.toString());
                        var type = RegExp.$1;
                        switch(type)
                        {
                            case "":
                                type = typeof(o[p]);
                            case "String":
                                type = "string"; break;
                            case "Number":
                                type = "int"; break;
                            case "Boolean":
                                type = "bool"; break;
                            case "Date":
                                type = "DateTime"; break;
                        }
                        s += "<" + type + ">" + SOAPClientParameters._serialize(o[p]) + "</" + type + ">"
                    }
                    else    // associative array
                        s += "<" + p + ">" + SOAPClientParameters._serialize(o[p]) + "</" + p + ">"
                }
            }
            // Object or custom function
            else
                for(var p in o)
                    s += "<" + p + ">" + SOAPClientParameters._serialize(o[p]) + "</" + p + ">";
            break;
        default:
            break; // throw new Error(500, "SOAPClientParameters: type '" + typeof(o) + "' is not supported");
    }
    return s;
}

function SOAPClient() {}

SOAPClient.simpleSoapRequest = function(url, ns, method, parameters)
{
    // build SOAP request
    var sr = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
             "<soap:Envelope " +
             "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" " +
             "xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" " +
             "xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">" +
             "<soap:Body>" +
             "<" + method + " xmlns=\"" + ns + "\">" +
             parameters.toXml() +
             "</" + method + "></soap:Body></soap:Envelope>";
    // send request
    var xmlHttp = SOAPClient._getXmlHttp();
    xmlHttp.open("POST", url, true);
    xmlHttp.send(sr);
}

// private: xmlhttp factory
SOAPClient._getXmlHttp = function() 
{
    try
    {
        if(window.XMLHttpRequest) 
        {
            var req = new XMLHttpRequest();
            // some versions of Moz do not support the readyState property and the onreadystate event so we patch it!
            if(req.readyState == null) 
            {
                req.readyState = 1;
                req.addEventListener("load", 
                    function() 
                    {
                        req.readyState = 4;
                        if(typeof req.onreadystatechange == "function")
                            req.onreadystatechange();
                    },
                    false);
            }
            return req;
        }
        if(window.ActiveXObject) 
            return new ActiveXObject(SOAPClient._getXmlHttpProgID());
    }
    catch (ex) {}
    throw new Error("Your browser does not support XmlHttp objects");
}
SOAPClient._getXmlHttpProgID = function()
{
    if(SOAPClient._getXmlHttpProgID.progid)
        return SOAPClient._getXmlHttpProgID.progid;
    var progids = ["Msxml2.XMLHTTP.5.0", "Msxml2.XMLHTTP.4.0", "MSXML2.XMLHTTP.3.0", "MSXML2.XMLHTTP", "Microsoft.XMLHTTP"];
    var o;
    for(var i = 0; i < progids.length; i++)
    {
        try
        {
            o = new ActiveXObject(progids[i]);
            return SOAPClient._getXmlHttpProgID.progid = progids[i];
        }
        catch (ex) {};
    }
    throw new Error("Could not find an installed XML parser");
}
