import React, { useEffect, useState } from "react";

const PhReading = () => {
  const [phValue, setPhValue] = useState("");
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchData = async () => {
      fetch("http://172.20.10.6/ph", { timeout: 5000 })
        .then((response) => {
          if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
          }
          setError(null);
          return response.json();
        })
        .then((data) => setPhValue(data))
        .catch((error) => {
          console.error("Error fetching PH:", error);
          setError(
            "Failed to fetch data. Please check the server and network."
          );
        });
    };
    const fetchDataInterval = setInterval(fetchData, 3000); // Fetch data every 5 seconds

    // Cleanup interval to avoid memory leaks
    return () => clearInterval(fetchDataInterval);
  }, []);
  console.log(phValue);
  return (
    <div>
      <p className="text-3xl font-bold underline">
        pH Value: {error ? error : 6.5}
      </p>
    </div>
  );
};

export default PhReading;
