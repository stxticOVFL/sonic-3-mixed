using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RSDKv5;

namespace ImpostorEditor2.Actions
{
    class ActionEntityPropertyChange : IAction
    {
        RSDKv5.Scene.ISCN_Object entity;
        string tag;
        object oldValue;
        object newValue;
        Action<RSDKv5.Scene.ISCN_Object, string, object, object> setValue;

        public ActionEntityPropertyChange(RSDKv5.Scene.ISCN_Object entity, string tag, object oldValue, object newValue, Action<RSDKv5.Scene.ISCN_Object, string, object, object> setValue)
        {
            this.entity = entity;
            this.tag = tag;
            this.oldValue = oldValue;
            this.newValue = newValue;
            this.setValue = setValue;
        }

        public void Undo()
        {
            setValue(entity, tag, oldValue, newValue);
        }

        public IAction Redo()
        {
            return new ActionEntityPropertyChange(entity, tag, newValue, oldValue, setValue);
        }
    }
}
