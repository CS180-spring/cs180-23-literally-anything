import Header from '../Components/Header'
import React, { useRef } from "react";

export default function CreateDataBase() {
    const inputRef = useRef<HTMLInputElement>(null);

    const handleUpload = () => {
      inputRef.current?.click();
    };
    return (
        <>
            <Header />
            <h2 style={{color: "black"}}> Create Database Page </h2>
            <div className="m-3">
                <label style={{color: "black"}}className="mx-3"> Choose file: </label>
                <input useRef={inputRef} className="d-none" type="file" />
                <button style={{backgroundColor: "#8A5AA4", color: "white", height: '50px', width: '100px'}}onClick={handleUpload} className="btn btn-outline-primary">
                    Upload
                </button>
            </div>
        </>
    )
}
