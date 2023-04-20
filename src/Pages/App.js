import './App.css';
import { BrowserRouter, Routes, Route } from 'react-router-dom';
import Home from './Pages/Home'
import CreateDataBase from './Pages/CreateDataBase'
import ViewDataBase from './Pages/ViewDataBase';
import NoPage from './Pages/NoPage';
function App() {


  return (
    <div className="App">
      <BrowserRouter>
        <Routes>
          <Route index element= {<Home />} />
          <Route path="/home" element={<Home />} />
          <Route path="/createDataBase" element={<CreateDataBase />} />
          <Route path="/viewDataBase" element ={<ViewDataBase />} />
          <Route path="*" element={<NoPage />} />
        </Routes>
      </BrowserRouter>
      
    </div>
  );
}

export default App;
