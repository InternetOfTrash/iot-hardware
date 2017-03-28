using InternetOfTrashHardware.Core.Strategies;


namespace InternetOfTrashHardware.Core
{
    interface ISense
    {
        ContainerLevel collectData();
        bool isActive();
        SensorContext getContext();
        bool setContext(SensorContext context);
    }

    class VirtualSensor : ISense
    {
        private SensorContext ctx;
        private int _counter = 1;
        private int _container , _fillLevel;
        bool active;
        
        public VirtualSensor(int id, int filllevel)
        {
            _fillLevel = filllevel;
            _container = id;
        }

        public ContainerLevel collectData()
        {
            if (_counter == 2)
            {
                _counter = 0;
                _fillLevel += 5;
            }
            if (_fillLevel > 99)
            {
                ContainerLevel temp = new ContainerLevel(_container,_fillLevel);
                _fillLevel = 0;
                return temp;
            }
            _counter++;
            
            return new ContainerLevel(_container,_fillLevel);
        }

        public SensorContext getContext()
        {
            return ctx;
        }

        public bool isActive()
        {
            return active;
        }

        public bool setContext(SensorContext context)
        {
            ctx  = context;
            if (ctx.ToString() == context.ToString()) return true;
            else return false;
        }

        private void run() {
            active = true;
        }
        private void pause()
        {
            active = false;
        }
    }
}
