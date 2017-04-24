using System;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Collections.Generic;


namespace helpdesk.Controllers
{
    public class LoginController : Controller
    {

       
        // GET: Login
        public ActionResult Index   (string id, int? x) 
        {
            int err = 0;


            ViewBag.tid = (id == null) ? "" : id;
            ViewBag.err = err;
            return View();
        }


        public ActionResult Welcome ()                  
        {
            return View();
        }
    }
}