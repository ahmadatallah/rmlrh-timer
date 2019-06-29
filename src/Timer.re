type state = { 
   seconds: int, 
   isTicking: bool
};

type action = 
  | Start 
  | Stop
  | Reset 
  | Tick;

[@react.component]
let make = () => {
   let initialState = { 
       isTicking: false,
       seconds: 30
   };
   let (state, dispatch) =  React.useReducer(
       (state, action) => 
          switch action {
          | Start => { ...state, isTicking: true }
          | Stop => { ...state, isTicking: false }
          | Reset => { ...state, seconds: 30 }
          | Tick => state.isTicking && state.seconds > 0
            ? {...state, seconds: state.seconds - 1} : state
          },
          initialState,
   );
   let dispatchStart = _event => dispatch(Start);
   let dispatchStop = _event => dispatch(Stop);
   let dispatchReset = _event => dispatch(Reset);


   React.useEffect(() => {
      let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
      // return of callback-function => cleanup 
      Some(() => Js.Global.clearInterval(timer));
   });
   
   <div>
    { ReasonReact.string(
        "Timer: " ++ string_of_int(state.seconds),
    )}
    {state.isTicking
        ? <Button
            onClick=dispatchStop
            title="STOP"
            category=Button.PRIMARY>
            "Stop"
         </Button>
        : <>
            <Button  
               onClick=dispatchStart
               title="START"
               category=Button.SECONDARY>
               "Start"
            </Button>
            <Button 
               onClick=dispatchReset
               title="RESET"
               category=Button.SECONDARY>
               "Reset"
            </Button>

          </>
    }
   </div>
};