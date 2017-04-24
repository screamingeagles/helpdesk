﻿using System.Web.Mvc;

namespace Helpdesk.Areas.Admin
{
    public class AdminAreaRegistration : AreaRegistration 
    {
        public override string AreaName 
        {
            get 
            {
                return "Admin";
            }
        }

        public override void RegisterArea(AreaRegistrationContext context) 
        {
            //context.MapRoute(
            //    "Admin_default",
            //    "Admin/{controller}/{action}/{id}",
            //    new { action = "Index", id = UrlParameter.Optional }
            //);

            context.MapRoute(
               "Admin_default",
               "Admin/{controller}/{action}/{id}",
               new { controller = "Login", action = "Index", id = UrlParameter.Optional },
               new[] { "Helpdesk.Areas.Admin.Controllers" }
           );
        }
    }
}