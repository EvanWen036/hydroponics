import React, { useEffect, useState } from "react";

const TotalDissolvedSolids = () => {
  const [tdsValue, setTdsValue] = useState("");
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchData = async () => {
      fetch("http://172.20.10.6/tds")
        .then((response) => {
          if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
          }
          setError(null);
          return response.json();
        })
        .then((data) => setTdsValue(data))
        .catch((error) => {
          console.error("Error fetching TDS:", error);
          setError(
            "Failed to fetch data. Please check the server and network."
          );
        });
    };
    const fetchDataInterval = setInterval(fetchData, 3000); // Fetch data every 5 seconds

    // Cleanup interval to avoid memory leaks
    return () => clearInterval(fetchDataInterval);
  }, []);
  console.log(tdsValue);
  return (
    <div>
      <p className="text-3xl font-bold underline">
        Tds Value: {error ? error : tdsValue}
      </p>
    </div>
  );
};

export default TotalDissolvedSolids;
