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
            <h2> Create Database Page </h2>
            <div className="m-3">
                <label className="mx-3">Choose file: </label>
                <input useRef={inputRef} className="d-none" type="file" />
                <button onClick={handleUpload} className="btn btn-outline-primary">
                    Upload
                </button>
            </div>
        </>
    )
}
