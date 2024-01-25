import logo from "./logo.svg";
import "./App.css";
import TotalDissolvedSolids from "./TotalDissolvedSolids";
import TDSValueBox from "./TDSValueBox";
import PhReading from "./PhReading";
import PhValueBox from "./PhValueBox";
function App() {
  const tds = <TotalDissolvedSolids />;
  return (
    <div className="App bg-peach h-screen">
      <div className="mb-12">
        <h2 className="flex justify-left pl-20 mb-1.5 font-semibold pt-32 text-brown text-2xl">
          {" "}
          Welcome to the{" "}
        </h2>
        <div className="flex flex-row">
          <h1 className="flex justify-left pl-20 font-semibold text-green-dark text-5xl">
            {" "}
            Duke Smart Home Hydroponic Garden{" "}
          </h1>
          <h1 className="font-semibold text-brown text-5xl">.</h1>
        </div>
      </div>
      <div className="flex flex-col mb-20">
        <p className="flex justify-left pl-20 text-brown text-xl">
          {" "}
          CREATED BY{" "}
        </p>
        <p className="flex justify-left pl-20 text-gray text-xl">
          {" "}
          Bryce Outten, Ella Etchandy, Evan Wen, Joshua Sadun, Maya Singla​{" "}
        </p>
      </div>
      <h1 className="flex justify-left pl-20 font-semibold text-green-dark text-5xl mb-4">
        {" "}
        GARDEN STATUS{" "}
      </h1>
      <div className="flex flex-row gap-y-2">
        <TDSValueBox />
        <PhValueBox />
      </div>
    </div>
  );
}

export default App;
