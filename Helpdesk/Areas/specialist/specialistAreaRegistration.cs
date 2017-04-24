using System.Web.Mvc;

namespace Helpdesk.Areas.specialist
{
    public class specialistAreaRegistration : AreaRegistration 
    {
        public override string AreaName 
        {
            get 
            {
                return "specialist";
            }
        }

        public override void RegisterArea(AreaRegistrationContext context) 
        {
            //context.MapRoute(
            //    "specialist_default",
            //    "specialist/{controller}/{action}/{id}",
            //    new { action = "Index", id = UrlParameter.Optional }
            //);

            context.MapRoute(
                "specialist_default",
                "specialist/{controller}/{action}/{id}",
                new { controller = "Login", action = "Index", id = UrlParameter.Optional },
                new[] { "Helpdesk.Areas.specialist.Controllers" }
            );
        }
    }
}