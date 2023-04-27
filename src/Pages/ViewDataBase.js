import Header from '../Components/Header'
import { Route, useNavigate, Link, Routes } from "react-router-dom";


export default function ViewDataBase() {

    return (
        <>
            <Header />
            <h2 style={{color: "white"}}> View Database Page </h2>
            <button
                style={{ backgroundColor: "#8A5AA4", color: "white", height: '60px', width: '100px' }}
                > Update Database
            </button>
            <button
                style={{ backgroundColor: "#8A5AA4", color: "white", height: '60px', width: '100px' }}
                > Delete Database
            </button>
 
        </>
    )
}
